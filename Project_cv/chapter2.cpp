#include "chapter2.h"
#include<QMenu>
#include<QAction>
#include<QFile>
QMenu* menu2[10];
QAction* act2[10];
Chapter2::Chapter2(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    CreatButton1();
}
//按键1--文本说明
void Chapter2::CreatButton1()
{

        act2[1] = new QAction("程序运行");
        act2[2] = new QAction("源码查看");

        act2[3] = new QAction("程序运行");
        act2[4] = new QAction("源码查看");

        act2[5] = new QAction("程序运行");
        act2[6] = new QAction("源码查看");

        act2[7] = new QAction("程序运行");
        act2[8] = new QAction("源码查看");




        menu2[1] = new QMenu("彩色目标跟踪");
        menu2[1]->addAction(act2[1]);
        menu2[1]->addAction(act2[2]);

        menu2[2] = new QMenu("光流法目标检测");
        menu2[2]->addAction(act2[3]);
        menu2[2]->addAction(act2[4]);

        menu2[3] = new QMenu("点追踪");
        menu2[3]->addAction(act2[5]);
        menu2[3]->addAction(act2[6]);

        menu2[4] = new QMenu("显示");
        menu2[4]->addMenu(menu2[1]);
        menu2[4]->addMenu(menu2[2]);
        menu2[4]->addMenu(menu2[3]);

        ui.C2PB1->setMenu(menu2[4]);
        connect(menu2[1],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_1Triggered1(QAction *)));
        connect(menu2[2],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_2Triggered1(QAction *)));
        connect(menu2[3],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_3Triggered1(QAction *)));
}
//chapter2 彩色物体追踪函数回调
void Chapter2::onMenu1_1Triggered1(QAction *action)
{
    if (action == act2[1])
    {
    Opencv::CamShiftDemo();
    }
    else if (action == act2[2])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/CamShiftDemo.txt");
    }

}
//chapter2 光流法物体追踪函数回调
void Chapter2::onMenu1_2Triggered1(QAction *action)
{
    if (action == act2[3])
    {
    Opencv::OpticFlow();
    }
    else if (action == act2[4])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/OpticFlow.txt");
    }

}
//chapter2 点追踪函数回调
void Chapter2::onMenu1_3Triggered1(QAction *action)
{
    if (action == act2[5])
    {
    Opencv::PointTracking();
    }
    else if (action == act2[6])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/PointTracking.txt");
    }

}
