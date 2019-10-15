#ifndef CHAPTER8_H
#define CHAPTER8_H
#include "ui_chapter8.h"
#include "opencv.h"
#include "dialog.h"

class Chapter8 : public QDialog
{
    Q_OBJECT

public:
    explicit Chapter8(QWidget *parent = 0);
    void CreateButton1();
    ~Chapter8(){}
private:
    Ui::Chapter8 ui;
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
};


#endif // CHAPTER8_H
