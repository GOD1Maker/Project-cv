#ifndef CHAPTER4_H
#define CHAPTER4_H
#include"ui_chapter4.h"
#include "opencv.h"
#include "dialog.h"

class Chapter4 : public QDialog
{
    Q_OBJECT

public:
    explicit Chapter4(QWidget *parent = 0);
    void CreateButton1();
    ~Chapter4(){}
private:
    Ui::Chapter4 ui;
private slots:
    void onMenu1_1Triggered1(QAction *action);
    void onMenu1_2Triggered1(QAction *action);
};

#endif // CHAPTER4_H
