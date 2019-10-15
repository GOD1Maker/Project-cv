#include "chapter6.h"
#include<QMenu>
#include<QAction>
#include<QFile>
QMenu* menu6[20];
QAction* act6[36];
Chapter6::Chapter6(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    CreateButton1();
}
void Chapter6::CreateButton1()
{
    act6[1] = new QAction("程序运行");
    act6[2] = new QAction("源码查看");

    act6[3] = new QAction("程序运行");
    act6[4] = new QAction("源码查看");

    act6[5] = new QAction("程序运行");
    act6[6] = new QAction("源码查看");

    act6[7] = new QAction("程序运行");
    act6[8] = new QAction("源码查看");

    act6[9] = new QAction("程序运行");
    act6[10] = new QAction("源码查看");

    act6[11] = new QAction("程序运行");
    act6[12] = new QAction("源码查看");

    act6[13] = new QAction("程序运行");
    act6[14] = new QAction("源码查看");

    act6[15] = new QAction("程序运行");
    act6[16] = new QAction("源码查看");

    act6[17] = new QAction("程序运行");
    act6[18] = new QAction("源码查看");

    act6[19] = new QAction("程序运行");
    act6[20] = new QAction("源码查看");

    act6[21] = new QAction("程序运行");
    act6[22] = new QAction("源码查看");

    act6[23] = new QAction("程序运行");
    act6[24] = new QAction("源码查看");

    act6[25] = new QAction("程序运行");
    act6[26] = new QAction("源码查看");

    act6[27] = new QAction("程序运行");
    act6[28] = new QAction("源码查看");

    act6[29] = new QAction("程序运行");
    act6[30] = new QAction("源码查看");

    menu6[1] = new QMenu("BoxFilter函数");
    menu6[1]->addAction(act6[1]);
    menu6[1]->addAction(act6[2]);

    menu6[2] = new QMenu("高斯模糊滤波");
    menu6[2]->addAction(act6[3]);
    menu6[2]->addAction(act6[4]);

    menu6[3] = new QMenu("MedianBlur函数");
    menu6[3]->addAction(act6[5]);
    menu6[3]->addAction(act6[6]);

    menu6[4] = new QMenu("双边滤波函数");
    menu6[4]->addAction(act6[7]);
    menu6[4]->addAction(act6[8]);

    menu6[5] = new QMenu("图像膨胀");
    menu6[5]->addAction(act6[9]);
    menu6[5]->addAction(act6[10]);

    menu6[6] = new QMenu("用morphologyEx进行图像膨胀");
    menu6[6]->addAction(act6[11]);
    menu6[6]->addAction(act6[12]);

    menu6[7] = new QMenu("用morphologyEx进行图像开运算");
    menu6[7]->addAction(act6[13]);
    menu6[7]->addAction(act6[14]);

    menu6[8] = new QMenu("用morphologyEx进行图像闭运算");
    menu6[8]->addAction(act6[15]);
    menu6[8]->addAction(act6[16]);

    menu6[9] = new QMenu("用morphologyEx进行形态学梯度运算");
    menu6[9]->addAction(act6[17]);
    menu6[9]->addAction(act6[18]);

    menu6[10] = new QMenu("用morphologyEx进行形态学顶帽运算");
    menu6[10]->addAction(act6[19]);
    menu6[10]->addAction(act6[20]);

    menu6[11] = new QMenu("用morphologyEx进行形态学黑帽运算");
    menu6[11]->addAction(act6[21]);
    menu6[11]->addAction(act6[22]);

    menu6[12] = new QMenu("漫水填充函数");
    menu6[12]->addAction(act6[23]);
    menu6[12]->addAction(act6[24]);

    menu6[13] = new QMenu("pyrup函数");
    menu6[13]->addAction(act6[25]);
    menu6[13]->addAction(act6[26]);

    menu6[14] = new QMenu("pyrdown函数");
    menu6[14]->addAction(act6[27]);
    menu6[14]->addAction(act6[28]);

    menu6[15] = new QMenu("基本阈值操作");
    menu6[15]->addAction(act6[29]);
    menu6[15]->addAction(act6[30]);

    menu6[16] = new QMenu("显示");
    menu6[16]->addMenu(menu6[1]);
    menu6[16]->addMenu(menu6[2]);
    menu6[16]->addMenu(menu6[3]);
    menu6[16]->addMenu(menu6[4]);
    menu6[16]->addMenu(menu6[5]);
    menu6[16]->addMenu(menu6[6]);
    menu6[16]->addMenu(menu6[7]);
    menu6[16]->addMenu(menu6[8]);
    menu6[16]->addMenu(menu6[9]);
    menu6[16]->addMenu(menu6[10]);
    menu6[16]->addMenu(menu6[11]);
    menu6[16]->addMenu(menu6[12]);
    menu6[16]->addMenu(menu6[13]);
    menu6[16]->addMenu(menu6[14]);
    menu6[16]->addMenu(menu6[15]);

    ui.C6PB1->setMenu(menu6[16]);
    connect(menu6[1],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_1Triggered1(QAction *)));
    connect(menu6[2],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_2Triggered1(QAction *)));
    connect(menu6[3],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_3Triggered1(QAction *)));
    connect(menu6[4],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_4Triggered1(QAction *)));
    connect(menu6[5],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_5Triggered1(QAction *)));
    connect(menu6[6],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_6Triggered1(QAction *)));
    connect(menu6[7],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_7Triggered1(QAction *)));
    connect(menu6[8],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_8Triggered1(QAction *)));
    connect(menu6[9],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_9Triggered1(QAction *)));
    connect(menu6[10],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_10Triggered1(QAction *)));
    connect(menu6[11],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_11Triggered1(QAction *)));
    connect(menu6[12],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_12Triggered1(QAction *)));
    connect(menu6[13],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_13Triggered1(QAction *)));
    connect(menu6[14],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_14Triggered1(QAction *)));
    connect(menu6[15],SIGNAL(triggered(QAction *)),this,SLOT(onMenu1_15Triggered1(QAction *)));
}
void Chapter6::onMenu1_1Triggered1(QAction *action)
{
    if (action == act6[1])
    {
    Opencv::BoxFilter();
    }
    else if (action == act6[2])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/BoxFilter.txt");
    }

}
void Chapter6::onMenu1_2Triggered1(QAction *action)
{
    if (action == act6[3])
    {
    Opencv::GuassianBlur();
    }
    else if (action == act6[4])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/GuassianFilter.txt");
    }

}
void Chapter6::onMenu1_3Triggered1(QAction *action)
{
    if (action == act6[5])
    {
    Opencv::MedianBlur();
    }
    else if (action == act6[6])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/MedianBlur.txt");
    }

}
void Chapter6::onMenu1_4Triggered1(QAction *action)
{
    if (action == act6[7])
    {
    Opencv::BilateralFilter();
    }
    else if (action == act6[8])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/BilateralFilter.txt");
    }

}
void Chapter6::onMenu1_5Triggered1(QAction *action)
{
    if (action == act6[9])
    {
    Opencv::Dilate();
    }
    else if (action == act6[10])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Dilate.txt");
    }

}
void Chapter6::onMenu1_6Triggered1(QAction *action)
{
    if (action == act6[11])
    {
    Opencv::DilationEx();
    }
    else if (action == act6[12])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/DilationEx.txt");
    }

}
void Chapter6::onMenu1_7Triggered1(QAction *action)
{
    if (action == act6[13])
    {
    Opencv::Opening();
    }
    else if (action == act6[14])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Opening.txt");
    }

}
void Chapter6::onMenu1_8Triggered1(QAction *action)
{
    if (action == act6[15])
    {
    Opencv::Closing();
    }
    else if (action == act6[16])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Closing.txt");
    }

}
void Chapter6::onMenu1_9Triggered1(QAction *action)
{
    if (action == act6[17])
    {
    Opencv::Gradient();
    }
    else if (action == act6[18])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Gradient.txt");
    }

}
void Chapter6::onMenu1_10Triggered1(QAction *action)
{
    if (action == act6[19])
    {
    Opencv::TopHat();
    }
    else if (action == act6[20])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/TopHat.txt");
    }

}
void Chapter6::onMenu1_11Triggered1(QAction *action)
{
    if (action == act6[21])
    {
    Opencv::BlackHat();
    }
    else if (action == act6[22])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/BlackHat.txt");
    }

}
void Chapter6::onMenu1_12Triggered1(QAction *action)
{
    if (action == act6[23])
    {
    Opencv::FloodFill();
    }
    else if (action == act6[24])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/FloodFill.txt");
    }

}
void Chapter6::onMenu1_13Triggered1(QAction *action)
{
    if (action == act6[25])
    {
    Opencv::PyrUp();
    }
    else if (action == act6[26])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/PyrUp.txt");
    }

}
void Chapter6::onMenu1_14Triggered1(QAction *action)
{
    if (action == act6[27])
    {
    Opencv::PyrDown();
    }
    else if (action == act6[28])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/PyrDown.txt");
    }

}
void Chapter6::onMenu1_15Triggered1(QAction *action)
{
    if (action == act6[29])
    {
    Opencv::Threshold();
    }
    else if (action == act6[30])
    {
    Dialog m;
    m.ShowCode("/Users/liuyuchen/QT_application/Project_cv/Threshold.txt");
    }

}

