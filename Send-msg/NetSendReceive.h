
#ifndef NETSNDRCV_H
#define NETSNDRCV_H

#include <QMainWindow>
#include "TcpServer.h"
#include "TcpClient.h"


namespace Ui {
class NetSndRcv;
}

class NetSndRcv : public QMainWindow
{
    Q_OBJECT

public:
    explicit NetSndRcv(QWidget *parent = nullptr);
    ~NetSndRcv();

private slots:
    void on_leClient1_returnPressed();
    void on_leServer_returnPressed();
    void on_leClient2_returnPressed();

    void onServerMessageReceived(QString message);
    void onClient1MessageReceived(QString message);
    void onClient2MessageReceived(QString message);

private:
    Ui::NetSndRcv *ui;

    TcpServer *m_server;
    TcpClient *m_client1, *m_client2;
};

#endif // NETSNDRCV_H
