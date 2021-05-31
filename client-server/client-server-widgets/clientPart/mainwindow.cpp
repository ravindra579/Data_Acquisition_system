#include "mainwindow.h"
#include "ui_mainwindow.h"
int i=1;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_disconnect->setVisible(false);
    client = new ClientStuff("localhost", 6547);
    setStatus(client->getStatus());
    connect(client, &ClientStuff::hasReadSome, this, &MainWindow::receivedSomething);
    connect(client, &ClientStuff::statusChanged, this, &MainWindow::setStatus);
    connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(gotError(QAbstractSocket::SocketError)));
}
MainWindow::~MainWindow()
{
    delete client;
    delete ui;
}
void MainWindow::setStatus(bool newStatus)
{
    if(newStatus)
    {
        ui->textEdit_log->append(tr("<font color=\"green\">CONNECTED</font>"));
        ui->pushButton_connect->setVisible(false);
        ui->pushButton_disconnect->setVisible(true);
    }
    else
    {
        if(i!=1){
        ui->textEdit_log->append(tr("<font color=\"red\">DISCONNECTED</font>"));
        }
        i++;
        ui->pushButton_connect->setVisible(true);
        ui->pushButton_disconnect->setVisible(false);
    }
}
void MainWindow::receivedSomething(QString msg)
{
    ui->textEdit_log->append(msg);
}
void MainWindow::gotError(QAbstractSocket::SocketError err)
{
    QString strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
            break;
        case 1:
            strError = "Remote host closed the connection";
            break;
        case 2:
            strError = "Host address was not found";
            break;
        case 5:
            strError = "Connection timed out";
            break;
        default:
            strError = "Unknown error";
    }
    ui->textEdit_log->append(strError);
}
void MainWindow::on_pushButton_connect_clicked()
{
    client->connect2host();
}
void MainWindow::on_pushButton_send_clicked()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << quint16(0) << ui->lineEdit_message->text();
    ui->lineEdit_message->clear();
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    client->tcpSocket->write(arrBlock);
}
void MainWindow::on_pushButton_disconnect_clicked()
{
    client->closeConnection();
}
