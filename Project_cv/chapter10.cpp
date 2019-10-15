#include "chapter10.h"
#include<QMenu>
#include<QAction>
#include<QFile>
QMenu* menu10[10];
QAction* act10[20];
Chapter10::Chapter10(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    CreatButton1();
}
//按键1--快速上手 创建
void Chapter10::CreatButton1()
{
    act10[1] = new QAction("程序运行");
    act10[2] = new QAction("源码查看");

    act10[3] = new QAction("程序运行");
    act10[4] = new QAction("源码查看");

    act10[5] = new QAction("程序运行");
    act10[6] = new QAction("源码查看");

    act10[7] = new QAction("程序运行");
    act10[8] = new QAction("源码查看");

    menu10[1] = new QMenu("cornerHarris函数用法");
    menu10[1]->addAction(act10[1]);
    menu10[1]->addAction(act10[2]);

    menu10[2] = new QMenu("Harris角点检测");
    menu10[2]->addAction(act10[3]);
    menu10[2]->addAction(act10[4]);

    menu10[3] = new QMenu("Shi-tomasi角点检测");
    menu10[3]->addAction(act10[5]);
    menu10[3]->addAction(act10[6]);

    menu10[4] = new QMenu("亚像素级检角点检测");
    menu10[4]->addAction(act10[7]);
    menu10[4]->addAction(act10[8]);


    menu10[5] = new QMenu("显示");
    menu10[5]->addMenu(menu10[1]);
    menu10[5]->addMenu(menu10[2]);
    menu10[5]->addMenu(menu10[3]);
    menu10[5]->addMenu(menu10[4]);

    ui.C10PB1->setMenu(menu10[5]);
    connect(menu10[1],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_1Triggered1(QAction *)));
    connect(menu10[2],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_2Triggered1(QAction *)));
    connect(menu10[3],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_3Triggered1(QAction *)));
    connect(menu10[4],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_4Triggered1(QAction *)));
}
void Chapter10::onMenu1_1Triggered1(QAction *action)
{
    if (action == act10[1])
    {
        Opencv::HarrisCorner();
    }
    else if(action == act10[2])
    {
        Dialog m;
        m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/HarrisCorner.txt");
    }
}
void Chapter10::onMenu1_2Triggered1(QAction *action)
{
    if (action == act10[3])
    {
        Opencv::HarrisCorner2();
    }
    else if(action == act10[4])
    {
        Dialog m;
        m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/HarrisCornerDetection.txt");
    }
}
void Chapter10::onMenu1_3Triggered1(QAction *action)
{
    if (action == act10[5])
    {
        Opencv::ShiTomasi();
    }
    else if(action == act10[6])
    {
        Dialog m;
        m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/ShiTomasi.txt");
    }
}
void Chapter10::onMenu1_4Triggered1(QAction *action)
{
    if (action == act10[7])
    {
        Opencv::CornerSubPix();
    }
    else if(action == act10[8])
    {
        Dialog m;
        m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/CornerSubPix.txt");
    }
}
