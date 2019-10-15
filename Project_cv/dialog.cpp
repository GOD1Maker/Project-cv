#include "dialog.h"
#include "ui_dialog.h"
#include<QFile>
#include <iostream>
using namespace std;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Code"));

}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::ShowCode(QString address)
{
    Dialog* dialog=new Dialog;
    dialog->setModal(false);    //此处ture为模态，false为非模态
    dialog->show();

    QFile *file=new QFile(address);
    file->open(QIODevice::ReadOnly);
    dialog->ui->text->setText(tr(file->readAll().data()));

}
