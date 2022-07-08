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
#include <unistd.h>


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
    static std::vector<key> keys;
    static QVector<QLabel*> labels;

    void CreateKeys();
    static void PressKeys(int index);
    static void ReadKeys();
    
    std::thread hook_thread;

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
