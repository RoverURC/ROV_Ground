#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  rov = new ROV;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
  joypad = new JoypadController();
  joypad->setJoypad(0); //Domyslny joypad
  connect(joypad,SIGNAL(axisChanged(int,qint16)),
           rov,SLOT(interpretAxis(int,qint16)));
  connect(joypad,SIGNAL(buttonChanged(int,bool)),
          rov,SLOT(interpretButton(int,bool)));


  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButtonConnect_clicked()
{
    rov->connectToRobot();
}

void MainWindow::on_pushButton_clicked()
{
  float array[2];
}
