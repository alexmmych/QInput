#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hook.h"

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
        uint16_t keyVC;
        int x;
        int y;
    };

    const static uint16_t KeyOrder[];

    std::vector<key> CreateKeys();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
