#ifndef CHAPTER1_H
#define CHAPTER1_H

#include "ui_chapter1.h"
#include "opencv.h"
#include "dialog.h"
class Chapter1 : public QDialog
{
    Q_OBJECT

public:
    explicit Chapter1(QWidget *parent = 0);
    void CreatButton1();
    void CreatButton2();
    ~Chapter1(){}
private:
    Ui::Chapter1 ui;

private slots:
        void onMenu1_1Triggered1(QAction *action);
        void onMenu1_2Triggered1(QAction *action);
        void onMenu1_3Triggered1(QAction *action);
        void onMenu1_4Triggered1(QAction *action);

        void onMenu2_1Triggered1(QAction *action);
        void onMenu2_2Triggered1(QAction *action);
};

#endif // CHAPTER1_H
