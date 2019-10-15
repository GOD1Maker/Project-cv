#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "opencv.h"
#include <QMainWindow>
#include "dialog.h"
#include "chapter1.h"
#include "chapter2.h"
#include "chapter3.h"
#include "chapter4.h"
#include "chapter5.h"
#include "chapter6.h"
#include "chapter7.h"
#include "chapter8.h"
#include "chapter9.h"
#include "chapter10.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void createButton_1();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Chapter1 *chapter1;
    Chapter2 *chapter2;
    Chapter3 *chapter3;
    Chapter4 *chapter4;
    Chapter5 *chapter5;
    Chapter6 *chapter6;
    Chapter7 *chapter7;
    Chapter8 *chapter8;
    Chapter9 *chapter9;
    Chapter10 *chapter10;
    //Dialog *dialog;
private slots:
        void timerUpDate();


};

#endif // MAINWINDOW_H
