#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void ShowCode(QString address);
    ~Dialog();

public:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
