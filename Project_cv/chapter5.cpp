#include "chapter5.h"
#include<QMenu>
#include<QAction>
#include<QFile>
QMenu* menu5[20];
QAction* act5[20];
Chapter5::Chapter5(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    CreateButton1();
}
void Chapter5::CreateButton1()
{
    act5[1] = new QAction("程序运行");
    act5[2] = new QAction("源码查看");

    act5[3] = new QAction("程序运行");
    act5[4] = new QAction("源码查看");

    act5[5] = new QAction("程序运行");
    act5[6] = new QAction("源码查看");

    act5[7] = new QAction("程序运行");
    act5[8] = new QAction("源码查看");

    act5[9] = new QAction("程序运行");
    act5[10] = new QAction("源码查看");

    act5[11] = new QAction("程序运行");
    act5[12] = new QAction("源码查看");

    act5[13] = new QAction("程序运行");
    act5[14] = new QAction("源码查看");

    menu5[1] = new QMenu("用指针访问像素");
    menu5[1]->addAction(act5[1]);
    menu5[1]->addAction(act5[2]);

    menu5[2] = new QMenu("用迭代器访问像素");
    menu5[2]->addAction(act5[3]);
    menu5[2]->addAction(act5[4]);

    menu5[3] = new QMenu("用动态地址计算配合at访问像素");
    menu5[3]->addAction(act5[5]);
    menu5[3]->addAction(act5[6]);

    menu5[4] = new QMenu("初级图像混合");
    menu5[4]->addAction(act5[7]);
    menu5[4]->addAction(act5[8]);

    menu5[5] = new QMenu("多通道图像混合");
    menu5[5]->addAction(act5[9]);
    menu5[5]->addAction(act5[10]);

    menu5[6] = new QMenu("改变图像对比度，亮度(按Q退出)");
    menu5[6]->addAction(act5[11]);
    menu5[6]->addAction(act5[12]);

    menu5[7] = new QMenu("离散傅立叶变换");
    menu5[7]->addAction(act5[13]);
    menu5[7]->addAction(act5[14]);

    menu5[10] = new QMenu("显示");
    menu5[10]->addMenu(menu5[1]);
    menu5[10]->addMenu(menu5[2]);
    menu5[10]->addMenu(menu5[3]);
    menu5[10]->addMenu(menu5[4]);
    menu5[10]->addMenu(menu5[5]);
    menu5[10]->addMenu(menu5[6]);
    menu5[10]->addMenu(menu5[7]);

    ui.C5PB1->setMenu(menu5[10]);
    connect(menu5[1],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_1Triggered1(QAction *)));
    connect(menu5[2],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_2Triggered1(QAction *)));
    connect(menu5[3],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_3Triggered1(QAction *)));
    connect(menu5[4],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_4Triggered1(QAction *)));
    connect(menu5[5],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_5Triggered1(QAction *)));
    connect(menu5[6],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_6Triggered1(QAction *)));
    connect(menu5[7],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_7Triggered1(QAction *)));

}
void Chapter5::onMenu1_1Triggered1(QAction *action)
{
    if (action == act5[1])
    {
    Opencv::UsePointerAccessPixel();
    }
    else if (action == act5[2])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/UsePointerAccessPixel.txt");
    }

}
void Chapter5::onMenu1_2Triggered1(QAction *action)
{
    if (action == act5[3])
    {
    Opencv::UseIteratorAccessPixel();
    }
    else if (action == act5[4])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/UseIteratorAccessPixel.txt");
    }

}
void Chapter5::onMenu1_3Triggered1(QAction *action)
{
    if (action == act5[5])
    {
    Opencv::UseAtAccessPixel();
    }
    else if (action == act5[6])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/UseAtAccessPixel.txt");
    }

}
void Chapter5::onMenu1_4Triggered1(QAction *action)
{
    if (action == act5[7])
    {
    Opencv::ImageBlending();
    }
    else if (action == act5[8])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/ImageBlending.txt");
    }

}
void Chapter5::onMenu1_5Triggered1(QAction *action)
{
    if (action == act5[9])
    {
    Opencv::MultiChannelImageBlending();
    }
    else if (action == act5[10])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/MultiChannelBlending.txt");
    }

}
void Chapter5::onMenu1_6Triggered1(QAction *action)
{
    if (action == act5[11])
    {
    Opencv::ChangeContrastAndBright();
    }
    else if (action == act5[12])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/ChangeContrastAndBright.txt");
    }

}
void Chapter5::onMenu1_7Triggered1(QAction *action)
{
    if (action == act5[13])
    {
    Opencv::DFT();
    }
    else if (action == act5[14])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/DFT.txt");
    }

}
