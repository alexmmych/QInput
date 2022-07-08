#include "include/mainwindow.h"

#include <QApplication>
#include <QDir>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(1456,600);

    w.show();

    return a.exec();
}
