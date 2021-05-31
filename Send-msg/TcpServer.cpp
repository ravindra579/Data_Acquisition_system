
#include "TcpServer.h"
#include <QByteArray>
#include <QDataStream>

TcpServer::TcpServer(QObject *parent) :
    QObject(parent)
{
}

bool TcpServer::startListening(const quint16 &port)
{
    bool isListening = false;

    if (! m_server)
    {
        m_server = new QTcpServer(this);
        isListening = m_server->listen(QHostAddress::AnyIPv4, port);

        if (isListening)
        {
            connect(m_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
        }
    }

    return isListening;
}

void TcpServer::onNewConnection()
{
    TcpConnection *connection = new TcpConnection(this, m_server->nextPendingConnection());
    m_connections.insert(connection);

    connect(connection, &TcpConnection::messageReceived, this, &TcpServer::onMessageReceived);
}

void TcpServer::sendMessage(const QString &message)
{
    foreach (TcpConnection *connection, m_connections)
    {
        if (connection->isValid())
            connection->sendMessage(message);
    }
}

void TcpServer::onMessageReceived(QString message)
{
    emit messageReceived(message);
}
