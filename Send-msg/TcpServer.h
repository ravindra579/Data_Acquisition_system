/* https://github.com/dehesselle/NetSendReceive
 */

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QString>
#include <QtNetwork/QTcpServer>
#include <QSet>
#include "TcpConnection.h"

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = nullptr);

    bool startListening(const quint16 &port);

    void sendMessage(const QString &message);

signals:
    void messageReceived(const QString &message);

private slots:
    void onNewConnection();
    void onMessageReceived(QString message);  ///< all clients connected here

private:
    QTcpServer *m_server = nullptr;

    QSet<TcpConnection*> m_connections;
};

#endif // TCPSERVER_H
