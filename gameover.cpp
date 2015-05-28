#include "gameover.h"
#include "ui_gameover.h"


gameover::gameover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
}

gameover::~gameover()
{
    delete ui;
}





void gameover::on_pushButton_clicked()
{
    this->close();
}
