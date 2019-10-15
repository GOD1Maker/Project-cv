#ifndef CHAPTER7_H
#define CHAPTER7_H
#include "ui_chapter7.h"
#include "opencv.h"
#include "dialog.h"

class Chapter7 : public QDialog
{
    Q_OBJECT

public:
    explicit Chapter7(QWidget *parent = 0);
    void CreateButton1();
    ~Chapter7(){}
private:
    Ui::Chapter7 ui;
private slots:
    void onMenu1_1Triggered1(QAction *action);
    void onMenu1_2Triggered1(QAction *action);
    void onMenu1_3Triggered1(QAction *action);
    void onMenu1_4Triggered1(QAction *action);
    void onMenu1_5Triggered1(QAction *action);
    void onMenu1_6Triggered1(QAction *action);
    void onMenu1_7Triggered1(QAction *action);
    void onMenu1_8Triggered1(QAction *action);
};

#endif // CHAPTER7_H
