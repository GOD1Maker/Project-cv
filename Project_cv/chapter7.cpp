#include "chapter7.h"
#include<QMenu>
#include<QAction>
#include<QFile>
QMenu* menu7[20];
QAction* act7[20];
Chapter7::Chapter7(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    CreateButton1();
}
void Chapter7::CreateButton1()
{
    act7[1] = new QAction("程序运行");
    act7[2] = new QAction("源码查看");

    act7[3] = new QAction("程序运行");
    act7[4] = new QAction("源码查看");

    act7[5] = new QAction("程序运行");
    act7[6] = new QAction("源码查看");

    act7[7] = new QAction("程序运行");
    act7[8] = new QAction("源码查看");

    act7[9] = new QAction("程序运行");
    act7[10] = new QAction("源码查看");

    act7[11] = new QAction("程序运行");
    act7[12] = new QAction("源码查看");

    act7[13] = new QAction("程序运行");
    act7[14] = new QAction("源码查看");

    act7[15] = new QAction("程序运行");
    act7[16] = new QAction("源码查看");

    menu7[1] = new QMenu("sobel算子");
    menu7[1]->addAction(act7[1]);
    menu7[1]->addAction(act7[2]);

    menu7[2] = new QMenu("Laplacian算子");
    menu7[2]->addAction(act7[3]);
    menu7[2]->addAction(act7[4]);

    menu7[3] = new QMenu("Scharr算子");
    menu7[3]->addAction(act7[5]);
    menu7[3]->addAction(act7[6]);

    menu7[4] = new QMenu("HoughLines函数");
    menu7[4]->addAction(act7[7]);
    menu7[4]->addAction(act7[8]);

    menu7[5] = new QMenu("HoughLinesP函数");
    menu7[5]->addAction(act7[9]);
    menu7[5]->addAction(act7[10]);

    menu7[6] = new QMenu("HoughCircles函数");
    menu7[6]->addAction(act7[11]);
    menu7[6]->addAction(act7[12]);

    menu7[7] = new QMenu("remap函数");
    menu7[7]->addAction(act7[13]);
    menu7[7]->addAction(act7[14]);

    menu7[8] = new QMenu("直方图均衡化");
    menu7[8]->addAction(act7[15]);
    menu7[8]->addAction(act7[16]);

    menu7[10] = new QMenu("显示");
    menu7[10]->addMenu(menu7[1]);
    menu7[10]->addMenu(menu7[2]);
    menu7[10]->addMenu(menu7[3]);
    menu7[10]->addMenu(menu7[4]);
    menu7[10]->addMenu(menu7[5]);
    menu7[10]->addMenu(menu7[6]);
    menu7[10]->addMenu(menu7[7]);
    menu7[10]->addMenu(menu7[8]);

    ui.C7PB1->setMenu(menu7[10]);
    connect(menu7[1],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_1Triggered1(QAction *)));
    connect(menu7[2],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_2Triggered1(QAction *)));
    connect(menu7[3],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_3Triggered1(QAction *)));
    connect(menu7[4],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_4Triggered1(QAction *)));
    connect(menu7[5],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_5Triggered1(QAction *)));
    connect(menu7[6],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_6Triggered1(QAction *)));
    connect(menu7[7],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_7Triggered1(QAction *)));
    connect(menu7[8],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_8Triggered1(QAction *)));

}
void Chapter7::onMenu1_1Triggered1(QAction *action)
{
    if (action == act7[1])
    {
    Opencv::Sobel_();
    }
    else if (action == act7[2])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Sobel.txt");
    }

}
void Chapter7::onMenu1_2Triggered1(QAction *action)
{
    if (action == act7[3])
    {
    Opencv::Laplacian_();
    }
    else if (action == act7[4])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Laplacian.txt");
    }

}
void Chapter7::onMenu1_3Triggered1(QAction *action)
{
    if (action == act7[5])
    {
    Opencv::Scharr_();
    }
    else if (action == act7[6])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Scharr.txt");
    }

}
void Chapter7::onMenu1_4Triggered1(QAction *action)
{
    if (action == act7[7])
    {
    Opencv::HoughLines_();
    }
    else if (action == act7[8])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/HoughLines.txt");
    }

}
void Chapter7::onMenu1_5Triggered1(QAction *action)
{
    if (action == act7[9])
    {
    Opencv::HoughLinesP_();
    }
    else if (action == act7[10])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/HoughLines.txt");
    }

}
void Chapter7::onMenu1_6Triggered1(QAction *action)
{
    if (action == act7[11])
    {
    Opencv::HoughCircles_();
    }
    else if (action == act7[12])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/HoughCircles.txt");
    }

}
void Chapter7::onMenu1_7Triggered1(QAction *action)
{
    if (action == act7[13])
    {
    Opencv::Remap_();
    }
    else if (action == act7[14])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Remap.txt");
    }

}
void Chapter7::onMenu1_8Triggered1(QAction *action)
{
    if (action == act7[15])
    {
    Opencv::EqualizeHist();
    }
    else if (action == act7[16])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/EqualizeHist.txt");
    }

}
