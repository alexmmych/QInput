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

    std::vector<key> keys = CreateKeys();

    for (MainWindow::key key : keys) {
        //Get the resource location
        QString resources = "/home/opensuse/keyboard-listener/resources/Dark/";

        resources += QString::fromStdString(key.name);

        QString url = (resources);
        QPixmap img(url);

        //Create a label for that image
        QLabel *label = new QLabel(this);

        label->setPixmap(img);
        label->setScaledContents(true);

        //Set it's position
        label->setGeometry(key.x,key.y,img.width(),img.height());
    }


    //Make background transparent
    setAttribute(Qt::WA_TranslucentBackground, true);
}

std::vector<MainWindow::key> MainWindow::CreateKeys() {
    //Open Key map
    std::ifstream file("layer-map.txt");

    std::vector<std::string> names;
    std::string input;

    std::vector<MainWindow::key> keys;

    std::string KeyName;
    int KeyX;
    int KeyY;

    while (file >> input){ //return file
        names.push_back(input);
    }

    std::vector<std::string>::iterator itr = names.begin();;

    for (std::string name : names) {
        //Create an iterator of the current name
        int index = std::distance(names.begin(),itr);

        int switch_case = index % 3;

        //Names will be divisibles of 3 (switch_case == 0) while X values will have 1 as rest and Y will have 2

        //std::cout << "At: " << index/3 << "; ";

        switch(switch_case) {
            case 0: {
                KeyName = name;
                break;
            }
            case 1: {
                KeyX = std::stoi(name.substr(1,name.length()-2));
                break;
            }
            case 2: {
                KeyY = std::stoi(name.substr(0,name.length()-1));

                key keyObj = {KeyName,KeyX,KeyY};
                keys.push_back(keyObj);

                break;
            }
        }
        std::advance(itr,1);
    }

    return keys;
}

MainWindow::~MainWindow()
{
    delete ui;
}

