#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hook.h"

#include <thread>

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    struct key {
        std::string name;
        short unsigned int keyVC;
        int x;
        int y;
    };

    const static uint16_t KeyOrder[];

    void CreateKeys();
    static std::vector<key> keys;
    static void ReadKeys();
    
    std::thread hook_thread;

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
