#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFrame>
#include <QtCore>
#include <QPixmap>
#include <QPalette>
#include <QMenuBar>
#include <QGraphicsOpacityEffect>
#include <QProxyStyle>
#include <QPainter>
class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 80; // 设置每个tabBar中item的大小
            s.rheight() = 65;
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;

                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0x555555);
                    painter->setBrush(QBrush(0x555555));
                    painter->drawRect(allRect.adjusted(6, 6, 6, -6));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);
                }
                else {
                    painter->setPen(0x5d5d5d);
                }

                painter->drawText(allRect, tab->text,option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
       ui->setupUi(this);
       //设置左上角图片及文字
       setWindowTitle(tr("OPENCV3"));
       setWindowIcon(QIcon("/Users/liuyuchen/QT_application/Project_cv/ICON.ico"));
       setFixedSize(400,1000);

       //设置时间
       QTimer *timer = new QTimer(this);
       connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
       timer->start(1000);

       //设置tabWidget透明度
       QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
       opacityEffect->setOpacity(20);
       ui->tabWidget_1->setGraphicsEffect(opacityEffect);

       ui->tabWidget_1->setTabPosition(QTabWidget::West);
       ui->tabWidget_1->tabBar()->setStyle(new CustomTabStyle);


       chapter1= new Chapter1;
       chapter2= new Chapter2;
       chapter3= new Chapter3;
       chapter4= new Chapter4;
       chapter5= new Chapter5;
       chapter6= new Chapter6;
       chapter7= new Chapter7;
       chapter8= new Chapter8;
       chapter9= new Chapter9;
       chapter10= new Chapter10;
       ui->tabWidget_1->insertTab(0,chapter1,"第一章");//添加Tab
       ui->tabWidget_1->insertTab(1,chapter2,"第二章");//添加Tab
       ui->tabWidget_1->insertTab(2,chapter3,"第三章");//添加Tab
       ui->tabWidget_1->insertTab(3,chapter4,"第四章");//添加Tab
       ui->tabWidget_1->insertTab(4,chapter5,"第五章");//添加Tab
       ui->tabWidget_1->insertTab(5,chapter6,"第六章");//添加Tab
       ui->tabWidget_1->insertTab(6,chapter7,"第七章");//添加Tab
       ui->tabWidget_1->insertTab(7,chapter8,"第八章");//添加Tab
       ui->tabWidget_1->insertTab(8,chapter9,"第九章");//添加Tab
       ui->tabWidget_1->insertTab(9,chapter10,"第十章");//添加Tab



}

MainWindow::~MainWindow()
{
    delete ui;
}
//更新及显示时间的回调函数
void MainWindow::timerUpDate()
{

QDateTime time = QDateTime::currentDateTime();
//获取系统现在的时间
QString str1 = time.toString("yyyy-MM-dd");
QString str2 = time.toString("hh:mm:ss dddd");
//设置系统时间显示格式
ui->label1->setText(str1);
ui->label2->setText(str2);
//在标签上显示时间
}


