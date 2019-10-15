#ifndef CHAPTER2_H
#define CHAPTER2_H

#include "ui_chapter2.h"
#include "opencv.h"
#include "dialog.h"
class Chapter2: public QDialog
{
    Q_OBJECT

public:
    explicit Chapter2(QWidget *parent = 0);
    void CreatButton1();
    ~Chapter2(){}
private:
    Ui::Chapter2 ui;

private slots:
        void onMenu1_1Triggered1(QAction *action);
        void onMenu1_2Triggered1(QAction *action);
        void onMenu1_3Triggered1(QAction *action);
};


#endif // CHAPTER2_H
