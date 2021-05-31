
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "TcpConnection.h"

class TcpClient : public TcpConnection
{
    Q_OBJECT
public:
    TcpClient(QObject *parent = nullptr);
};

#endif // TCPCLIENT_H
