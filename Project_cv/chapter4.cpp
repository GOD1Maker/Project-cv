#include "chapter4.h"
#include<QMenu>
#include<QAction>
#include<QFile>
QMenu* menu4[10];
QAction* act4[20];
Chapter4::Chapter4(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    CreateButton1();
}
void Chapter4::CreateButton1()
{

    act4[2] = new QAction("源码查看");

    act4[3] = new QAction("程序运行");
    act4[4] = new QAction("源码查看");

    menu4[1] = new QMenu("基础图像容器");
    menu4[1]->addAction(act4[2]);

    menu4[2] = new QMenu("用Opencv绘图");
    menu4[2]->addAction(act4[3]);
    menu4[2]->addAction(act4[4]);

    menu4[3] = new QMenu("显示");
    menu4[3]->addMenu(menu4[1]);
    menu4[3]->addMenu(menu4[2]);

    ui.C4PB1->setMenu(menu4[3]);
    connect(menu4[1],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_1Triggered1(QAction *)));
    connect(menu4[2],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_2Triggered1(QAction *)));

}
//chapter4 UseMat函数回调
void Chapter4::onMenu1_1Triggered1(QAction *action)
{
    if (action == act4[2])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/UseMat.txt");
    }

}
//chapter4 DrawImage函数回调
void Chapter4::onMenu1_2Triggered1(QAction *action)
{
    if (action == act4[3])
    {
    Opencv::DrawImage();
    }
    else if (action == act4[4])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/DrawImage.txt");
    }

}


