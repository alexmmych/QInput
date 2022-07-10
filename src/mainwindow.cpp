#include "include/mainwindow.h"
#include "./ui_mainwindow.h"

const uint16_t MainWindow::KeyOrder[] = {
    VC_ESCAPE,
    VC_F1,
    VC_F2,
    VC_F3,
    VC_F4,
    VC_F5,
    VC_F6,
    VC_F7,
    VC_F8,
    VC_F9,
    VC_F10,
    VC_F11,
    VC_F12,
    VC_BACKQUOTE,
    VC_1,
    VC_2,
    VC_3,
    VC_4,
    VC_5,
    VC_6,
    VC_7,
    VC_8,
    VC_9,
    VC_0,
    VC_MINUS,
    VC_EQUALS,
    VC_BACKSPACE,
    VC_TAB,
    VC_Q,
    VC_W,
    VC_E,
    VC_R,
    VC_T,
    VC_Y,
    VC_U,
    VC_I,
    VC_O,
    VC_P,
    VC_OPEN_BRACKET,
    VC_CLOSE_BRACKET,
    VC_ENTER,
    VC_CAPS_LOCK,
    VC_A,
    VC_S,
    VC_D,
    VC_F,
    VC_G,
    VC_H,
    VC_J,
    VC_K,
    VC_L,
    VC_SEMICOLON,
    VC_QUOTE,
    VC_SHIFT_L,
    VC_Z,
    VC_X,
    VC_C,
    VC_V,
    VC_B,
    VC_N,
    VC_M,
    VC_COMMA,
    VC_PERIOD,
    VC_SLASH,
    VC_CONTROL_L,
    VC_META_L,
    VC_ALT_L,
    VC_SPACE
};

std::vector<MainWindow::key> MainWindow::keys;
int MainWindow::index;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<MainWindow::key> tempKeys = CreateKeys();

    //Creates each key
    for (MainWindow::key key : tempKeys) {
        //Get the resource location
        QString resources = QCoreApplication::applicationDirPath();

        resources += "/resources/Dark/";
        resources += QString::fromStdString(key.name);

        QString url = (resources);
        QPixmap img(url);

        //Create a label for that image
        QLabel *label = new QLabel(this);

        label->setObjectName(QString::fromStdString(key.name));
        label->setPixmap(img);
        label->setScaledContents(true);

        //Set it's position
        label->setGeometry(key.x,key.y,img.width(),img.height());

        key.label = label;

        //Set pressed Pixmap

        QString newResource = QCoreApplication::applicationDirPath();
        newResource += "/resources/Light/";

        std::string newString = key.name;
        size_t pos = (newString.find("Dark"));

        newString.replace(pos,4,"Light");

        newResource += QString::fromStdString(newString);
        QString newUrl = (newResource);
        QPixmap pressedImg(newUrl);

        key.nonPressed = img;
        key.Pressed = pressedImg;

        keys.push_back(key);
    }

    if (WIN32) {
        setWindowFlag(Qt::FramelessWindowHint);
    }

    //Make background transparent
    setAttribute(Qt::WA_TranslucentBackground, true);

    //Create a hook instance
    Hook newHook;

    //Create hook thread
    hook_thread = std::thread(&Hook::RunHook,newHook);
}

void MainWindow::key::PressKey() {
    label->setPixmap(Pressed);
}

void MainWindow::key::ReleaseKey() {
    label->setPixmap(nonPressed);
}

void MainWindow::GetIndex() {
    auto it = std::find_if(MainWindow::keys.begin(), MainWindow::keys.end(), [&cm = Hook::Keycode] (const MainWindow::key& m) -> bool {return cm == m.keyVC; });
        
    if (it != MainWindow::keys.end()) {
        MainWindow::index = it - MainWindow::keys.begin();
    }
}


std::vector<MainWindow::key> MainWindow::CreateKeys() {
    //Open Key map
    std::ifstream file("resources/Layout/layer-map.txt");

    std::vector<std::string> names;
    std::vector<MainWindow::key> tempKeys;
    std::string input;

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
                std::cout << "Name: " << name << "  At: " << index/3 << std::endl;
                break;
            }
            case 1: {
                KeyX = std::stoi(name.substr(1,name.length()-2));
                break;
            }
            case 2: {
                KeyY = std::stoi(name.substr(0,name.length()-1));

                key keyObj;
                keyObj.name = KeyName;
                keyObj.keyVC = MainWindow::KeyOrder[index/3];
                keyObj.x = KeyX;
                keyObj.y = KeyY;
                tempKeys.push_back(keyObj);
                break;
            }
        }
        std::advance(itr,1);
    }
    return tempKeys;
}

MainWindow::~MainWindow()
{
    Hook::StopHook();
    
    hook_thread.join();

    delete ui;
}

