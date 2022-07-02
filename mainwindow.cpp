#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//Initial test of png rendering

    QString url = R"(/home/opensuse/Documents/Keyboard.png)";
    QPixmap img(url);

    ui->label->setPixmap(img);
    ui->label->setScaledContents(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

