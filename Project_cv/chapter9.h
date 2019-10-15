#ifndef CHAPTER9_H
#define CHAPTER9_H

#include "ui_chapter9.h"
#include "opencv.h"
#include "dialog.h"

class Chapter9 : public QDialog
{
    Q_OBJECT

public:
    explicit Chapter9(QWidget *parent = 0);
    void CreateButton1();
    ~Chapter9(){}
private:
    Ui::Chapter9 ui;
private slots:
    void onMenu1_1Triggered1(QAction *action);
    void onMenu1_2Triggered1(QAction *action);
    void onMenu1_3Triggered1(QAction *action);
    void onMenu1_4Triggered1(QAction *action);
    void onMenu1_5Triggered1(QAction *action);
};


#endif // CHAPTER9_H
