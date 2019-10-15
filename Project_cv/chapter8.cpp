#include "chapter8.h"
#include<QMenu>
#include<QAction>
#include<QFile>
QMenu* menu8[20];
QAction* act8[20];
Chapter8::Chapter8(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    CreateButton1();
}
void Chapter8::CreateButton1()
{
    act8[1] = new QAction("程序运行");
    act8[2] = new QAction("源码查看");

    act8[3] = new QAction("程序运行");
    act8[4] = new QAction("源码查看");

    act8[5] = new QAction("程序运行");
    act8[6] = new QAction("源码查看");

    act8[7] = new QAction("程序运行");
    act8[8] = new QAction("源码查看");

    act8[9] = new QAction("程序运行");
    act8[10] = new QAction("源码查看");

    act8[11] = new QAction("程序运行");
    act8[12] = new QAction("源码查看");

    act8[13] = new QAction("程序运行");
    act8[14] = new QAction("源码查看");

    act8[15] = new QAction("程序运行");
    act8[16] = new QAction("源码查看");

    act8[17] = new QAction("程序运行");
    act8[18] = new QAction("源码查看");

    menu8[1] = new QMenu("轮廓检测");
    menu8[1]->addAction(act8[1]);
    menu8[1]->addAction(act8[2]);

    menu8[2] = new QMenu("凸包检测");
    menu8[2]->addAction(act8[3]);
    menu8[2]->addAction(act8[4]);

    menu8[3] = new QMenu("寻找并绘制物体的凸包");
    menu8[3]->addAction(act8[5]);
    menu8[3]->addAction(act8[6]);

    menu8[4] = new QMenu("创建包围轮廓的矩形边界");
    menu8[4]->addAction(act8[7]);
    menu8[4]->addAction(act8[8]);

    menu8[5] = new QMenu("创建包围轮廓的圆形边界");
    menu8[5]->addAction(act8[9]);
    menu8[5]->addAction(act8[10]);

    menu8[6] = new QMenu("创建包围轮廓的矩形和圆形边界框");
    menu8[6]->addAction(act8[11]);
    menu8[6]->addAction(act8[12]);

    menu8[7] = new QMenu("查找和绘制图片轮廓矩");
    menu8[7]->addAction(act8[13]);
    menu8[7]->addAction(act8[14]);

    menu8[8] = new QMenu("分水岭算法（使用鼠标画线，按1或空格处理，按2恢复原图，按ESC退出）");
    menu8[8]->addAction(act8[15]);
    menu8[8]->addAction(act8[16]);

    menu8[9] = new QMenu("图像修补（使用鼠标画线，按1或空格处理，按2恢复原图，按ESC退出）");
    menu8[9]->addAction(act8[17]);
    menu8[9]->addAction(act8[18]);

    menu8[10] = new QMenu("显示");
    menu8[10]->addMenu(menu8[1]);
    menu8[10]->addMenu(menu8[2]);
    menu8[10]->addMenu(menu8[3]);
    menu8[10]->addMenu(menu8[4]);
    menu8[10]->addMenu(menu8[5]);
    menu8[10]->addMenu(menu8[6]);
    menu8[10]->addMenu(menu8[7]);
    menu8[10]->addMenu(menu8[8]);
    menu8[10]->addMenu(menu8[9]);

    ui.C8PB1->setMenu(menu8[10]);
    connect(menu8[1],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_1Triggered1(QAction *)));
    connect(menu8[2],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_2Triggered1(QAction *)));
    connect(menu8[3],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_3Triggered1(QAction *)));
    connect(menu8[4],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_4Triggered1(QAction *)));
    connect(menu8[5],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_5Triggered1(QAction *)));
    connect(menu8[6],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_6Triggered1(QAction *)));
    connect(menu8[7],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_7Triggered1(QAction *)));
    connect(menu8[8],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_8Triggered1(QAction *)));
    connect(menu8[9],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_9Triggered1(QAction *)));
}
void Chapter8::onMenu1_1Triggered1(QAction *action)
{
    if (action == act8[1])
    {
    Opencv::FindContours();
    }
    else if (action == act8[2])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/FindContours.txt");
    }

}
void Chapter8::onMenu1_2Triggered1(QAction *action)
{
    if (action == act8[3])
    {
    Opencv::ConvexHull();
    }
    else if (action == act8[4])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/ConvexHull.txt");
    }

}
void Chapter8::onMenu1_3Triggered1(QAction *action)
{
    if (action == act8[5])
    {
    Opencv::ConvexHull2();
    }
    else if (action == act8[6])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/ConvexHull2.txt");
    }

}
void Chapter8::onMenu1_4Triggered1(QAction *action)
{
    if (action == act8[7])
    {
    Opencv::MinAreaRect();
    }
    else if (action == act8[8])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/minAreaRect.txt");
    }

}
void Chapter8::onMenu1_5Triggered1(QAction *action)
{
    if (action == act8[9])
    {
    Opencv::MinEnclosingCircle();
    }
    else if (action == act8[10])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/MinEnclosingCircle.txt");
    }

}
void Chapter8::onMenu1_6Triggered1(QAction *action)
{
    if (action == act8[11])
    {
    Opencv::ApproxPolyDP();
    }
    else if (action == act8[12])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/ApproxPolyDP.txt");
    }

}
void Chapter8::onMenu1_7Triggered1(QAction *action)
{
    if (action == act8[13])
    {
    Opencv::ContourMoment();
    }
    else if (action == act8[14])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/ContourMoment.txt");
    }

}
void Chapter8::onMenu1_8Triggered1(QAction *action)
{
    if (action == act8[15])
    {
    Opencv::WaterShed();
    }
    else if (action == act8[16])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/WaterShed.txt");
    }

}
void Chapter8::onMenu1_9Triggered1(QAction *action)
{
    if (action == act8[17])
    {
    Opencv::Inpaint();
    }
    else if (action == act8[18])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Inpaint.txt");
    }

}
