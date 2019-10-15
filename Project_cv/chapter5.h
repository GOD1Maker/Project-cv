#ifndef CHAPTER5_H
#define CHAPTER5_H
#include"ui_chapter5.h"
#include "opencv.h"
#include "dialog.h"

class Chapter5 : public QDialog
{
    Q_OBJECT

public:
    explicit Chapter5(QWidget *parent = 0);
    void CreateButton1();
    ~Chapter5(){}
private:
    Ui::Chapter5 ui;
private slots:
    void onMenu1_1Triggered1(QAction *action);
    void onMenu1_2Triggered1(QAction *action);
    void onMenu1_3Triggered1(QAction *action);
    void onMenu1_4Triggered1(QAction *action);
    void onMenu1_5Triggered1(QAction *action);
    void onMenu1_6Triggered1(QAction *action);
    void onMenu1_7Triggered1(QAction *action);
};


#endif // CHAPTER5_H
