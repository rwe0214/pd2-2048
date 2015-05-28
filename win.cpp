#include "win.h"
#include "ui_win.h"

win::win(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::win)
{
    ui->setupUi(this);
}

win::~win()
{
    delete ui;
}

void win::on_pushButton_clicked()
{
    this->close();
}
