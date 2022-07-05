#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLabel>
#include <QString>
#include <QLineEdit>

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Open Key map
    std::ifstream file("layer-map.txt");

    std::vector<std::string> names;
    std::string input;

    while (file >> input){ //return file
        names.push_back(input);
    }

    //Get the desired png
    QString resources = "/home/opensuse/keyboard-listener/resources/Dark/";

    resources += QString::fromStdString(names.at(0));

    std::vector<std::string>::iterator itr;

    for (std::string name : names) {
        //Create an iterator of the current name
        itr = std::find(names.begin(),names.end(),name);
        int index = std::distance(names.begin(),itr);
        //Names will be divsibles of 3
        if (index % 3 == 0) {
            std::cout << "At: " << index/3 << "; ";
            std::cout << name << std::endl;
        }
    }

    QString url = (resources);
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

