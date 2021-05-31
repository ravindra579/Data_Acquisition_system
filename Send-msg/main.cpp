
#include "NetSendReceive.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetSndRcv w;
    w.show();

    return a.exec();
}
