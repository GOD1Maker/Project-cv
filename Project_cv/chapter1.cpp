#include "chapter1.h"
#include<QMenu>
#include<QAction>
#include<QFile>
QMenu* menu1[10];
QAction* act1[20];
Chapter1::Chapter1(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    CreatButton1();
    CreatButton2();
}
//按键1--快速上手 创建
void Chapter1::CreatButton1()
{
        act1[1] = new QAction("程序运行");
        act1[2] = new QAction("源码查看");

        act1[3] = new QAction("程序运行");
        act1[4] = new QAction("源码查看");

        act1[5] = new QAction("程序运行");
        act1[6] = new QAction("源码查看");

        act1[7] = new QAction("程序运行");
        act1[8] = new QAction("源码查看");

        menu1[1] = new QMenu("图像显示");
        menu1[1]->addAction(act1[1]);
        menu1[1]->addAction(act1[2]);

        menu1[2] = new QMenu("图像腐蚀");
        menu1[2]->addAction(act1[3]);
        menu1[2]->addAction(act1[4]);

        menu1[3] = new QMenu("图像模糊");
        menu1[3]->addAction(act1[5]);
        menu1[3]->addAction(act1[6]);

        menu1[4] = new QMenu("canny边缘");
        menu1[4]->addAction(act1[7]);
        menu1[4]->addAction(act1[8]);

        menu1[5] = new QMenu("显示");
        menu1[5]->addMenu(menu1[1]);
        menu1[5]->addMenu(menu1[2]);
        menu1[5]->addMenu(menu1[3]);
        menu1[5]->addMenu(menu1[4]);

        ui.PB1->setMenu(menu1[5]);
        connect(menu1[1],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_1Triggered1(QAction *)));
        connect(menu1[2],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_2Triggered1(QAction *)));
        connect(menu1[3],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_3Triggered1(QAction *)));
        connect(menu1[4],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_4Triggered1(QAction *)));

}

//按键1子菜单图像显示回调
void Chapter1::onMenu1_1Triggered1(QAction *action)
{
    if (action == act1[1])
    {
    Opencv::PhotoShow();
    }
    else if (action == act1[2])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/ShowImage.txt");
    }

}
//按键1子菜单图像腐蚀回调
void Chapter1::onMenu1_2Triggered1(QAction *action)
{

    if (action == act1[3])
    {
    Opencv::PhotoErosion();
    }
    else if (action == act1[4])
    {
        Dialog m;
        m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/ImageErode.txt");
    }


}
//按键1子菜单图像模糊回调
void Chapter1::onMenu1_3Triggered1(QAction *action)
{
    if (action == act1[5])
    {
    Opencv::PhotoBlur();
    }
    else if (action == act1[6])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/BlurImage.txt");
    }
}
//按键1子菜单canny边缘检测回调
void Chapter1::onMenu1_4Triggered1(QAction *action)
{
    if (action == act1[7])
    {
     Opencv::PhotoCanny();
    }
    else if (action == act1[8])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Canny.txt");
    }
}

//按键2--视频操作 创建
void Chapter1::CreatButton2()
{
    act1[9] = new QAction("程序运行");
    act1[10] = new QAction("源码查看");

    act1[11] = new QAction("程序运行");
    act1[12] = new QAction("源码查看");

    menu1[6] = new QMenu("视频读取");
    menu1[6]->addAction(act1[9]);
    menu1[6]->addAction(act1[10]);

    menu1[7] = new QMenu("调用摄像");
    menu1[7]->addAction(act1[11]);
    menu1[7]->addAction(act1[12]);

    menu1[8] = new QMenu("显示");
    menu1[8]->addMenu(menu1[6]);
    menu1[8]->addMenu(menu1[7]);
    ui.PB2->setMenu(menu1[8]);

    connect(menu1[6],SIGNAL(triggered(QAction *)),this,SLOT(onMenu2_1Triggered1(QAction *)));
    connect(menu1[7],SIGNAL(triggered(QAction *)),this,SLOT(onMenu2_2Triggered1(QAction *)));

}
//按键2子菜单视频播放回调
void Chapter1::onMenu2_1Triggered1(QAction *action)
{
    if (action == act1[9])
    {
    Opencv::PlayVideo();
    }
    else if (action == act1[10])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/PlayVideo.txt");
    }
}
//按键2子菜单摄像头调用回调
void Chapter1::onMenu2_2Triggered1(QAction *action)
{
    if (action == act1[11])
    {
    Opencv::UseCamera();
    }
    else if (action == act1[12])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/ShowImage.txt");
    }
}
