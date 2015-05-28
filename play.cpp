#include "play.h"
#include "ui_play.h"

play::play(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::play)
{
    ui->setupUi(this);

    srand((unsigned)time(NULL));

    score=0;

    QPixmap pic0(":/new/prefix1/0.jpg");
    QPixmap pic2(":/new/prefix1/2.jpg");
    QPixmap pic4(":/new/prefix1/4.jpg");
    QPixmap pic8(":/new/prefix1/8.jpg");
    QPixmap pic16(":/new/prefix1/16.jpg");
    QPixmap pic32(":/new/prefix1/32.jpg");
    QPixmap pic64(":/new/prefix1/64.jpg");
    QPixmap pic128(":/new/prefix1/128.jpg");
    QPixmap pic256(":/new/prefix1/256.jpg");
    QPixmap pic512(":/new/prefix1/512.jpg");
    QPixmap pic1024(":/new/prefix1/1024.jpg");
    QPixmap pic2048(":/new/prefix1/2048.jpg");
    QPixmap pic4096(":/new/prefix1/4096.jpg");

    pic[0]=pic0;pic[2]=pic2;pic[4]=pic4;pic[8]=pic8;pic[16]=pic16;pic[32]=pic32;
    pic[64]=pic64;pic[128]=pic128;pic[256]=pic256;pic[512]=pic512;pic[1024]=pic1024;pic[2048]=pic2048;pic[4096]=pic4096;

}

void play::setlabel(int i,int j,int k)
{//匯入圖片
    switch(i)
    {
        case 0: switch(j)
        {
            case 0: ui->label_00->setPixmap(pic[k]);break;
            case 1: ui->label_01->setPixmap(pic[k]);break;
            case 2: ui->label_02->setPixmap(pic[k]);break;
            case 3: ui->label_03->setPixmap(pic[k]);break;
        }break;
        case 1: switch(j)
        {
            case 0: ui->label_10->setPixmap(pic[k]);break;
            case 1: ui->label_11->setPixmap(pic[k]);break;
            case 2: ui->label_12->setPixmap(pic[k]);break;
            case 3: ui->label_13->setPixmap(pic[k]);break;
        }break;
        case 2: switch(j)
        {
            case 0: ui->label_20->setPixmap(pic[k]);break;
            case 1: ui->label_21->setPixmap(pic[k]);break;
            case 2: ui->label_22->setPixmap(pic[k]);break;
            case 3: ui->label_23->setPixmap(pic[k]);break;
        }break;
        case 3: switch(j)
        {
            case 0: ui->label_30->setPixmap(pic[k]);break;
            case 1: ui->label_31->setPixmap(pic[k]);break;
            case 2: ui->label_32->setPixmap(pic[k]);break;
            case 3: ui->label_33->setPixmap(pic[k]);break;
        }break;
    }



}

void play::keyPressEvent(QKeyEvent *press)
{
    if(press->key()==Qt::Key_A)
    {
        play::A_move();
        play::setmap();
    }
    if(press->key()==Qt::Key_S)
    {
        play::S_move();
        play::setmap();
    }
    if(press->key()==Qt::Key_W)
    {
        play::W_move();
        play::setmap();
    }
    if(press->key()==Qt::Key_D)
    {
        play::D_move();
        play::setmap();
    }
}

void play::startmap()
{//初始化
    int i,j,k;
    k=2;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            map[i][j]=0;
    }

    i=rand()%4;
    j=rand()%4;

    map[i][j]=k;

    play::setlabel(i,j,k);

    i=rand()%4;
    j=rand()%4;

    while(map[i][j]!=0)
    {
        i=rand()%4;
        j=rand()%4;
    }

    map[i][j]=k;
    play::setlabel(i,j,k);


}

void play::setmap()
{//隨機產生2方格
    int i,j,k,l;
    k=2;l=0;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(map[i][j]==0)
                l++;//判斷空格數量
            if(map[i][j]==2048)//勝利條件
            {
                z.show();

            }
        }
    }
    play::chk();
    if(c==16)//c=16時表示不能進行合併或移動了
    {
        for(i=0;i<4;i++)
        {   //歸零
            for(j=0;j<4;j++)
            {
                map[i][j]=0;
            }
        }
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
               play::setlabel(i,j,0);
            }
        }
        //重新開始遊戲
        play::startmap();
        g.show();//顯示gameover
    }
    else if(A==16||S==16||W==16||D==16)return;//任一方向無法再合併或移動
    else
    {
        if(l==0)return;//如果空格數為零表示沒有地方可以產生隨機方格
        else
        {
            i=rand()%4;
            j=rand()%4;

            while(map[i][j]!=0)
            {
                i=rand()%4;
                j=rand()%4;
            }

            map[i][j]=k;
            play::setlabel(i,j,k);
        }
    }
}


void play::A_move()
{//向左
    int i,j,k,m;
    //初始化檢查矩陣
    A=0,S=0,W=0,D=0;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            check[i][j]=map[i][j];
    }

    for(i=0;i<4;i++)
    {   //全部往左推
        for(j=1;j<4;j++)
        {
            k=j;
            while(map[i][k-1]==0)
            {
                map[i][k-1]=map[i][k];
                map[i][k]=0;
                k--;
                if(k==0)break;
            }
        }
        //檢查是否合併
        for(j=1;j<4;j++)
        {
            if(map[i][j-1]==map[i][j])
            {
                m=map[i][j-1];
                m*=2;
                score+=m;
                point.setNum(score);
                ui->label->setText(point);

                map[i][j-1]=m;
                map[i][j]=0;
            }

            k=j;
            while(map[i][k-1]==0)
            {
                map[i][k-1]=map[i][k];
                map[i][k]=0;
                k--;
                if(k==0)break;
            }
        }
    }
    //如果新的矩陣和檢查矩陣相同代表此方向不能再進行移動或合併，在setmap()裡將不再產生隨機的2方格
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(check[i][j]==map[i][j])
                A++;
        }
    }
    for(i=0;i<4;i++)
    {   //產生圖像
        for(j=0;j<4;j++)
        {
            if(map[i][j]==0)
            {
                play::setlabel(i,j,0);
                continue;
            }
            else
            {
                k=map[i][j];
                play::setlabel(i,j,k);
            }
        }
    }

}

void play::S_move()
{//向下
    int i,j,k,m;
    //初始化檢查矩陣
    A=0,S=0,W=0,D=0;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            check[i][j]=map[i][j];
    }

    for(j=0;j<4;j++)
    {//全部往下推
        for(i=2;i>=0;i--)
        {
            k=i;
            while(map[k+1][j]==0)
            {
                map[k+1][j]=map[k][j];
                map[k][j]=0;
                k++;
                if(k==3)break;
            }
        }
        //檢查是否合併
        for(i=2;i>=0;i--)
        {
            if(map[i+1][j]==map[i][j])
            {
                m=map[i+1][j];
                m*=2;
                score+=m;
                point.setNum(score);
                ui->label->setText(point);
                map[i+1][j]=m;
                map[i][j]=0;
            }
            k=i;
            while(map[k+1][j]==0)
            {
                map[k+1][j]=map[k][j];
                map[k][j]=0;
                k++;
                if(k==3)break;
            }
        }
    }
    //如果新的矩陣和檢查矩陣相同代表此方向不能再進行移動或合併，在setmap()裡將不再產生隨機的2方格
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(check[i][j]==map[i][j])
                S++;
        }
    }
    for(i=0;i<4;i++)
    {   //產生圖像
        for(j=0;j<4;j++)
        {
            if(map[i][j]==0)
            {
                play::setlabel(i,j,0);
                continue;
            }
            else
            {
                k=map[i][j];
                play::setlabel(i,j,k);
            }
        }
    }

}

void play::W_move()
{//向上
    int i,j,k,m;
    //初始化檢查矩陣
    A=0,S=0,W=0,D=0;

    //初始化檢查矩陣
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            check[i][j]=map[i][j];
    }

    for(j=0;j<4;j++)
    {//全部往上推
        for(i=1;i<4;i++)
        {
            k=i;
            while(map[k-1][j]==0)
            {
                map[k-1][j]=map[k][j];
                map[k][j]=0;
                k--;
                if(k==0)break;
            }
        }
        //檢查是否合併
        for(i=1;i<4;i++)
        {
            if(map[i-1][j]==map[i][j])
            {
                m=map[i-1][j];
                m*=2;
                score+=m;
                point.setNum(score);
                ui->label->setText(point);
                map[i-1][j]=m;
                map[i][j]=0;
            }
            k=i;
            while(map[k-1][j]==0)
            {
                map[k-1][j]=map[k][j];
                map[k][j]=0;
                k--;
                if(k==0)break;
            }
        }
    }
    //如果新的矩陣和檢查矩陣相同代表此方向不能再進行移動或合併，在setmap()裡將不再產生隨機的2方格
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(check[i][j]==map[i][j])
                W++;
        }
    }
    for(i=0;i<4;i++)
    {   //產生圖像
        for(j=0;j<4;j++)
        {
            if(map[i][j]==0)
            {
                play::setlabel(i,j,0);
                continue;
            }
            else
            {
                k=map[i][j];
                play::setlabel(i,j,k);
            }
        }
    }

}

void play::D_move()
{//向上
    int i,j,k,m;
    //初始化檢查矩陣
    A=0,S=0,W=0,D=0;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            check[i][j]=map[i][j];
    }

    for(i=0;i<4;i++)
    {   //全部往右推
        for(j=2;j>=0;j--)
        {
            k=j;
            while(map[i][k+1]==0)
            {
                map[i][k+1]=map[i][k];
                map[i][k]=0;
                k++;
                if(k==3)break;
            }
        }
        //檢查是否合併
        for(j=2;j>=0;j--)
        {
            if(map[i][j+1]==map[i][j])
            {
                m=map[i][j+1];
                m*=2;
                score+=m;
                point.setNum(score);
                ui->label->setText(point);
                map[i][j+1]=m;
                map[i][j]=0;
            }
            k=j;
            while(map[i][k+1]==0)
            {
                map[i][k+1]=map[i][k];
                map[i][k]=0;
                k++;
                if(k==3)break;
            }
        }
    }
    //如果新的矩陣和檢查矩陣相同代表此方向不能再進行移動或合併，在setmap()裡將不再產生隨機的2方格
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(check[i][j]==map[i][j])
                D++;
        }
    }
    for(i=0;i<4;i++)
    {   //產生圖像
        for(j=0;j<4;j++)
        {
            if(map[i][j]==0)
            {
                play::setlabel(i,j,0);
                continue;
            }
            else
            {
                k=map[i][j];
                play::setlabel(i,j,k);
            }
        }
    }
}

void play::chk()
{//檢查gameover的條件
    //檢查所有方向是否能再進行合併，不能即代表遊戲結束
    int i,j;
    c=0;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            if(map[i][j]==0)
                return;
    }
    //檢查中間四個
    for(i=1;i<3;i++)
    {
        for(j=1;j<3;j++)
        {
            if(map[i][j]!=map[i+1][j]&&map[i][j]!=map[i-1][j]&&map[i][j]!=map[i][j+1]&&map[i][j]!=map[i][j-1])
                c++;
        }
    }
    //檢查四個角落
    if(map[0][0]!=map[0][1]&&map[0][0]!=map[1][0])c++;
    if(map[3][0]!=map[2][0]&&map[3][0]!=map[3][1])c++;
    if(map[0][3]!=map[0][2]&&map[0][3]!=map[1][3])c++;
    if(map[3][3]!=map[3][2]&&map[3][3]!=map[2][3])c++;
    //檢查剩餘的八個
    if(map[0][1]!=map[0][0]&&map[0][1]!=map[0][2]&&map[0][1]!=map[1][1])c++;
    if(map[0][2]!=map[0][1]&&map[0][2]!=map[0][3]&&map[0][2]!=map[1][2])c++;
    if(map[1][0]!=map[0][0]&&map[1][0]!=map[2][0]&&map[1][0]!=map[1][1])c++;
    if(map[2][0]!=map[1][0]&&map[2][0]!=map[3][0]&&map[2][0]!=map[2][1])c++;
    if(map[3][1]!=map[3][0]&&map[3][1]!=map[3][2]&&map[3][1]!=map[2][1])c++;
    if(map[3][2]!=map[3][1]&&map[3][2]!=map[3][3]&&map[3][2]!=map[2][2])c++;
    if(map[1][3]!=map[0][3]&&map[1][3]!=map[2][3]&&map[1][3]!=map[1][2])c++;
    if(map[2][3]!=map[1][3]&&map[2][3]!=map[3][3]&&map[2][3]!=map[2][2])c++;
}



play::~play()
{
    delete ui;
}

void play::on_pushButton_clicked()
{
    int i,j;
    for(i=0;i<4;i++)
    {   //歸零
        for(j=0;j<4;j++)
        {
            map[i][j]=0;
        }
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
           play::setlabel(i,j,0);
        }
    }
    play::startmap();
}

void play::on_pushButton_2_clicked()
{
    this->close();
}
