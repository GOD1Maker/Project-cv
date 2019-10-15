#include "chapter9.h"
#include<QMenu>
#include<QAction>
#include<QFile>
QMenu* menu9[20];
QAction* act9[20];
Chapter9::Chapter9(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    CreateButton1();
}
void Chapter9::CreateButton1()
{
    act9[1] = new QAction("程序运行");
    act9[2] = new QAction("源码查看");

    act9[3] = new QAction("程序运行");
    act9[4] = new QAction("源码查看");

    act9[5] = new QAction("程序运行");
    act9[6] = new QAction("源码查看");

    act9[7] = new QAction("程序运行");
    act9[8] = new QAction("源码查看");

    act9[9] = new QAction("程序运行");
    act9[10] = new QAction("源码查看");

    act9[11] = new QAction("程序运行");
    act9[12] = new QAction("源码查看");

    menu9[1] = new QMenu("二维直方图的绘制");
    menu9[1]->addAction(act9[1]);
    menu9[1]->addAction(act9[2]);

    menu9[2] = new QMenu("一维直方图的绘制");
    menu9[2]->addAction(act9[3]);
    menu9[2]->addAction(act9[4]);

    menu9[3] = new QMenu("RGB三色直方图的绘制");
    menu9[3]->addAction(act9[5]);
    menu9[3]->addAction(act9[6]);

    menu9[4] = new QMenu("反向投射");
    menu9[4]->addAction(act9[7]);
    menu9[4]->addAction(act9[8]);

    menu9[5] = new QMenu("模版匹配");
    menu9[5]->addAction(act9[9]);
    menu9[5]->addAction(act9[10]);

    menu9[10] = new QMenu("显示");
    menu9[10]->addMenu(menu9[1]);
    menu9[10]->addMenu(menu9[2]);
    menu9[10]->addMenu(menu9[3]);
    menu9[10]->addMenu(menu9[4]);
    menu9[10]->addMenu(menu9[5]);

    ui.C9PB1->setMenu(menu9[10]);
    connect(menu9[1],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_1Triggered1(QAction *)));
    connect(menu9[2],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_2Triggered1(QAction *)));
    connect(menu9[3],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_3Triggered1(QAction *)));
    connect(menu9[4],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_4Triggered1(QAction *)));
    connect(menu9[5],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_5Triggered1(QAction *)));
}
void Chapter9::onMenu1_1Triggered1(QAction *action)
{
    if (action == act9[1])
    {
    Opencv::HS_Histogram();
    }
    else if (action == act9[2])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/HS_Histogram.txt");
    }

}
void Chapter9::onMenu1_2Triggered1(QAction *action)
{
    if (action == act9[3])
    {
    Opencv::Histogram2();
    }
    else if (action == act9[4])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Histogram2.txt");
    }

}
void Chapter9::onMenu1_3Triggered1(QAction *action)
{
    if (action == act9[5])
    {
    Opencv::Histogram3();
    }
    else if (action == act9[6])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Histogram3.txt");
    }

}
void Chapter9::onMenu1_4Triggered1(QAction *action)
{
    if (action == act9[7])
    {
    Opencv::CalcBackProject();
    }
    else if (action == act9[8])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/CalcBackProject.txt");
    }

}
void Chapter9::onMenu1_5Triggered1(QAction *action)
{
    if (action == act9[9])
    {
    Opencv::MatchTemplate();
    }
    else if (action == act9[10])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/MatchTemplate.txt");
    }

}
