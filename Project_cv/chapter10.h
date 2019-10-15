#ifndef CHAPTER10_H
#define CHAPTER10_H
#include "ui_chapter10.h"
#include "opencv.h"
#include "dialog.h"
class Chapter10 : public QDialog
{
    Q_OBJECT

public:
    explicit Chapter10(QWidget *parent = 0);
    void CreatButton1();
    ~Chapter10(){}
private:
    Ui::Chapter10 ui;

private slots:
        void onMenu1_1Triggered1(QAction *action);
        void onMenu1_2Triggered1(QAction *action);
        void onMenu1_3Triggered1(QAction *action);
        void onMenu1_4Triggered1(QAction *action);

};
#endif // CHAPTER10_H
