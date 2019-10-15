#include "mainwindow.h"
#include <QApplication>
#include "chapter1.h"
#include "chapter2.h"
#include "chapter3.h"
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    w->show();
    QApplication::exit(0);
    return a.exec();
}
