#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <rov.h>
#include <joypadcontroller.h>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButtonConnect_clicked();

  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;
  ROV *rov;
  JoypadController *joypad;
};

#endif // MAINWINDOW_H
