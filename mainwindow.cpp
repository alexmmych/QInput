#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLabel>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Get the desired png
    QString url = ("/home/opensuse/keyboard-listener/Esc_Key_Dark.png");
    QPixmap img(url);

    //Create a label for that image
    QLabel *label = new QLabel(this);

    label->setPixmap(img);
    label->setScaledContents(false);

    //Set it's position
    label->setGeometry(0,0,img.width(),img.height());

    //Make background transparent
    setAttribute(Qt::WA_TranslucentBackground, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

