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

    std::vector<std::string>::iterator itr = names.begin();;

    for (std::string name : names) {
        //Create an iterator of the current name
        int index = std::distance(names.begin(),itr);

        int switch_case = index % 3;

        //Names will be divisibles of 3 (switch_case == 0) while X values will have 1 as rest and Y will have 2

        std::cout << "At: " << index/3 << "; ";

        switch(switch_case) {
            case 0: {
                std::cout << "Name: " << name << std::endl;
                break;
            }
            case 1: {
                std::cout << "X: " << name.substr(1,name.length()-2) << std::endl;
                break;
            }
            case 2: {
                std::cout << "Y: " << name.substr(0,name.length()-1) << std::endl;
                break;
            }
        }
        std::advance(itr,1);
    }


    //Get the desired png
    QString resources = "/home/opensuse/keyboard-listener/resources/Dark/";

    resources += QString::fromStdString(names.at(0));

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

