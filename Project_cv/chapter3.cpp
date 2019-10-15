#include "chapter3.h"
#include<QMenu>
#include<QAction>
#include<QFile>
QMenu* menu3[10];
QAction* act3[20];
Chapter3::Chapter3(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    CreatButton1();
}
void Chapter3::CreatButton1()
{
    act3[1] = new QAction("程序运行");
    act3[2] = new QAction("源码查看");

    act3[3] = new QAction("程序运行");
    act3[4] = new QAction("源码查看");

    act3[5] = new QAction("程序运行");
    act3[6] = new QAction("源码查看");

    act3[7] = new QAction("程序运行");
    act3[8] = new QAction("源码查看");

    menu3[1] = new QMenu("使用Imwrite生成透明图像");
    menu3[1]->addAction(act3[1]);
    menu3[1]->addAction(act3[2]);

    menu3[2] = new QMenu("图像的载入，显示和输出");
    menu3[2]->addAction(act3[3]);
    menu3[2]->addAction(act3[4]);

    menu3[3] = new QMenu("为程序界面添加滑动条");
    menu3[3]->addAction(act3[5]);
    menu3[3]->addAction(act3[6]);

    menu3[4] = new QMenu("基本鼠标操作");
    menu3[4]->addAction(act3[7]);
    menu3[4]->addAction(act3[8]);

    menu3[5] = new QMenu("显示");
    menu3[5]->addMenu(menu3[1]);
    menu3[5]->addMenu(menu3[2]);
    menu3[5]->addMenu(menu3[3]);
    menu3[5]->addMenu(menu3[4]);

    ui.C3PB1->setMenu(menu3[5]);
    connect(menu3[1],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_1Triggered1(QAction *)));
    connect(menu3[2],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_2Triggered1(QAction *)));
    connect(menu3[3],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_3Triggered1(QAction *)));
    connect(menu3[4],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_4Triggered1(QAction *)));
}
//chapter3 Imwrite函数回调
void Chapter3::onMenu1_1Triggered1(QAction *action)
{
    if (action == act3[1])
    {
    Opencv::UseImwrite();
    }
    else if (action == act3[2])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/UseImwrite.txt");
    }

}
//chapter3 LoadShowOutput函数回调
void Chapter3::onMenu1_2Triggered1(QAction *action)
{
    if (action == act3[3])
    {
    Opencv::LoadShowOutput();
    }
    else if (action == act3[4])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/LoadShowOutput.txt");
    }
}
//chapter3 CreateTrackBar函数回调
void Chapter3::onMenu1_3Triggered1(QAction *action)
{
    if (action == act3[5])
    {
    Opencv::CreateTrackBar();
    }
    else if (action == act3[6])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/CreateTrackBar.txt");
    }
}
//chapter3 UseMouse函数回调
void Chapter3::onMenu1_4Triggered1(QAction *action)
{
    if (action == act3[7])
    {
    Opencv::UseMouse();
    }
    else if (action == act3[8])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/UseMouse.txt");
    }
}

