/* https://github.com/dehesselle/NetSendReceive
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QString>

class TcpConnection : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnection(QObject *parent = nullptr);    ///< for client usage
    TcpConnection(QObject *parent, QTcpSocket *socket);   ///< for server usage

    const bool &isValid();

    void sendMessage(QString message);
    bool connectTo(QString host, quint16 port);

signals:
    void messageReceived(QString message);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *m_socket;
    quint16 m_blockSize = 0;
    bool m_isValid;
};

#endif // CONNECTION_H
