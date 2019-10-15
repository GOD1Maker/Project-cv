#ifndef CHAPTER6_H
#define CHAPTER6_H
#include "ui_chapter6.h"
#include "opencv.h"
#include "dialog.h"

class Chapter6 : public QDialog
{
    Q_OBJECT

public:
    explicit Chapter6(QWidget *parent = 0);
    void CreateButton1();
    ~Chapter6(){}
private:
    Ui::Chapter6 ui;
private slots:
    void onMenu1_1Triggered1(QAction *action);
    void onMenu1_2Triggered1(QAction *action);
    void onMenu1_3Triggered1(QAction *action);
    void onMenu1_4Triggered1(QAction *action);
    void onMenu1_5Triggered1(QAction *action);
    void onMenu1_6Triggered1(QAction *action);
    void onMenu1_7Triggered1(QAction *action);
    void onMenu1_8Triggered1(QAction *action);
    void onMenu1_9Triggered1(QAction *action);
    void onMenu1_10Triggered1(QAction *action);
    void onMenu1_11Triggered1(QAction *action);
    void onMenu1_12Triggered1(QAction *action);
    void onMenu1_13Triggered1(QAction *action);
    void onMenu1_14Triggered1(QAction *action);
    void onMenu1_15Triggered1(QAction *action);
};

#endif // CHAPTER6_H
