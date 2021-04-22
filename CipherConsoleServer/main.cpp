#include <QCoreApplication>

#include "cipherstcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CiphersTcpServer server;

    return a.exec();
}
