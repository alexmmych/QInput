#include "include/mainwindow.h"
#include "include/hook.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(1456,600);

    w.show();

    Hook newHook;

    return a.exec();
}
