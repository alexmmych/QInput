#include "include/mainwindow.h"
#include "include/hook.h"

#include <QApplication>
#include <QDir>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(1456,600);

    w.show();

    Hook newHook;

    //Will only act after hook_stop()
    printf("YOU GOT THE RAWCODE: %#06x \n",Hook::Rawcode);

    return a.exec();
}
