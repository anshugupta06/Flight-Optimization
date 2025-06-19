#include "mainwindow.h"

#include <QApplication>
#include <QDebug>  // For debug messages

int main(int argc, char *argv[])
{
    qDebug() << "Starting the application...";  // Debug message at startup
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
