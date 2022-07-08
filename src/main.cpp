#include "include/mainwindow.h"

#include <QApplication>
#include <QDir>

#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(1456,600);

    w.show();

    Hook newHook;

    std::thread hook_thread(&Hook::RunHook,newHook);

    return a.exec();
}
