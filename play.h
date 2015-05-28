#ifndef PLAY_H
#define PLAY_H

#include <QDialog>
#include <time.h>
#include <math.h>
#include <QKeyEvent>
#include <QString>
#include "gameover.h"
#include "win.h"

namespace Ui {
class play;
}

class play : public QDialog
{
    Q_OBJECT

public:
    explicit play(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *press);
    void setlabel(int,int,int);
    void startmap();
    void setmap();
    void A_move();
    void S_move();
    void W_move();
    void D_move();
    void chk();
    ~play();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::play *ui;
    int map[4][4],check[4][4];
    QPixmap pic[4096];
    int score,c,A,S,W,D;
    QString point;
    gameover g;
    win z;
};

#endif // PLAY_H
