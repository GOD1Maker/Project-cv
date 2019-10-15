#ifndef CHAPTER3_H
#define CHAPTER3_H
#include"ui_chapter3.h"
#include "opencv.h"
#include "dialog.h"
class Chapter3: public QDialog
{
    Q_OBJECT

public:
    explicit Chapter3(QWidget *parent = 0);
    void CreatButton1();
    ~Chapter3(){}
private:
    Ui::Chapter3 ui;

private slots:
    void onMenu1_1Triggered1(QAction *action);
    void onMenu1_2Triggered1(QAction *action);
    void onMenu1_3Triggered1(QAction *action);
    void onMenu1_4Triggered1(QAction *action);
};

#endif // CHAPTER3_H
