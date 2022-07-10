#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hook.h"

#include <thread>

#include <QMainWindow>

#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QDir>
#include <QVector>

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>

#include <chrono>
#include <thread>



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
        QLabel* label;
        QPixmap nonPressed;
        QPixmap Pressed;
        int x;
        int y;
        void PressKey();
        void ReleaseKey();
    };

    static std::vector<key> keys;
    static int index;

    static void SetIndex();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    
    std::vector<key> CreateKeys();
    std::thread hook_thread;
    const static uint16_t KeyOrder[];
};
#endif // MAINWINDOW_H
