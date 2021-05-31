

#include "NetSendReceive.h"
#include "ui_NetSndRcv.h"

NetSndRcv::NetSndRcv(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NetSndRcv)
{
    ui->setupUi(this);

    m_server = new TcpServer(this);

    if (m_server->startListening(2157))
        ui->lstServer->addItem("Server started.");
    else
        ui->lstServer->addItem("Server failed to start.");

    m_client1 = new TcpClient(this);
    if (m_client1->connectTo("localhost", 2157))
        ui->lstClient1->addItem("Connected.");
    else
        ui->lstClient1->addItem("Failed to connect.");

    m_client2 = new TcpClient(this);
    if (m_client2->connectTo("localhost", 2157))
        ui->lstClient2->addItem("Connected.");
    else
        ui->lstClient2->addItem("Failed to connect.");

    connect(m_server,  &TcpServer::messageReceived, this, &NetSndRcv::onServerMessageReceived);
    connect(m_client1, &TcpClient::messageReceived, this, &NetSndRcv::onClient1MessageReceived);
    connect(m_client2, &TcpClient::messageReceived, this, &NetSndRcv::onClient2MessageReceived);
}

NetSndRcv::~NetSndRcv()
{
    delete ui;
}

void NetSndRcv::on_leClient1_returnPressed()
{
    m_client1->sendMessage(ui->leClient1->text());
    ui->lstClient1->addItem(ui->leClient1->text());
    ui->leClient1->clear();
}

void NetSndRcv::on_leClient2_returnPressed()
{
    m_client2->sendMessage(ui->leClient2->text());
    ui->lstClient2->addItem(ui->leClient2->text());
    ui->leClient2->clear();

}

void NetSndRcv::on_leServer_returnPressed()
{
    m_server->sendMessage(ui->leServer->text());
    ui->lstServer->addItem(ui->leServer->text());
    ui->leServer->clear();

}

void NetSndRcv::onClient1MessageReceived(QString message)
{
    ui->lstClient1->addItem(message);
}

void NetSndRcv::onClient2MessageReceived(QString message)
{
    ui->lstClient2->addItem(message);
}

void NetSndRcv::onServerMessageReceived(QString message)
{
    ui->lstServer->addItem(message);
}
