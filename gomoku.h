#ifndef GOMOKU_H
#define GOMOKU_H

#include<mainwindow.h>
#include<QLabel>
#include<QPushButton>
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>
#include<QFont>
#include<vector>
#include<QtGlobal>
#include<QTime>
#include<QComboBox>
using namespace std;

struct Point{
    int x,y;

    void operator =(const Point &a)
    {
        x=a.x;y=a.y;
    }

    Point operator +(const Point &a)const
    {
        Point p={x+a.x,y+a.y};
        return p;
    }

    Point operator -(const Point &a)const
    {
        Point p={x-a.x,y-a.y};
        return p;
    }

    Point operator *(const int &a)const
    {
        Point p={x*a,y*a};
        return p;
    }

    bool operator ==(const Point &a)const
    {
        return (x==a.x&&y==a.y);
    }

    void operator +=(const Point &a)
    {
        *this=*this+a;
    }

    void operator -=(const Point &a)
    {
        *this=*this-a;
    }

    void operator *=(const int &a)
    {
        *this=*this*a;
    }
};

struct Point_With_Score{
    Point p;
    int score;
    bool operator <(const Point_With_Score &T)const{
        return score < T.score;
    }
};

class gomoku
{
public:
    gomoku()
    {
        clear();
    }

    void clear();
    void step(Point p);
    void check(Point p);
    void win(int who);

    bool played(Point p);
    int player();
    bool ifwin();
    bool legal(Point p);
private:
    int board[20][20];
    const Point fx[8]={{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
    bool now,end;
    int winner;
    bool lft(Point p);
    bool up(Point p);
    bool zs(Point p);
    bool zx(Point p);
};

class mygomokuAI
{
public:
    mygomokuAI()
    {
        clear();
    }

    void clear();
    Point step(Point p);

    void setlevel(int x);
    void setwho(int x);
private:
    int level,me,Value_Me,Value_Enemy;
    int board[20][20];
    const int Inf = (1<<29);
    const Point fx[8]={{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
    const int dir[9][2]={
    {0,0},
    {0,1},
    {1,1},
    {1,0},
    {1,-1},
    {0,-1},
    {-1,-1},
    {-1,0},
    {-1,1}};

    bool legal(Point p);

    int evaluate(int x,int y,int color,int v);
    int check(int v);
    int min_max(int v,int dep,int a,int b);
    bool isWin(int v);
    bool blank(int x,int y);
    Point move();
};

class mywin : public MainWindow
{
    Q_OBJECT
public:
    mywin()
    {
        this->setGeometry(700,100,600,800);
        this->setWindowTitle("gomoku by temp06");
        bk.load(":/new/icon/black");
        wt.load(":/new/icon/white");
        bk.scaled(30,30,Qt::KeepAspectRatio);
        wt.scaled(30,30,Qt::KeepAspectRatio);
        for(int i=1;i<=15;i++) for(int j=1;j<=15;j++)
        {
           blk[i][j].setParent(this);wht[i][j].setParent(this);
           blk[i][j].setGeometry(40*(i-1)+5,200+40*(j-1)+5,30,30);
           wht[i][j].setGeometry(40*(i-1)+5,200+40*(j-1)+5,30,30);
           blk[i][j].setPixmap(bk);blk[i][j].setScaledContents(true);
           wht[i][j].setPixmap(wt);wht[i][j].setScaledContents(true);
        }
        reset.setParent(this);
        reset.setGeometry(250,50,100,100);
        pvp.setParent(this);
        pvp.setGeometry(100,50,100,100);
        pve.setParent(this);
        pve.setGeometry(400,50,100,100);
        txt.setParent(this);
        txt.setGeometry(100,150,400,50);
        txt.setAlignment(Qt::AlignHCenter);
        myfont.setPointSize(20);
        myfont.setFamily("微软雅黑");
        txt.setFont(myfont);
        pvp.setText("人机对战");
        pve.setText("人类对战");
        reset.setText("重新开始");
        ifAI=0;
        QObject::connect(&reset,&QPushButton::clicked,this,&mywin::clear);
        QObject::connect(&pvp,&QPushButton::clicked,this,&mywin::topvp);
        QObject::connect(&pve,&QPushButton::clicked,this,&mywin::topve);
        clear();
    }

    void clear();

private:
    gomoku game;
    mygomokuAI AI;
    int who;
    bool end,ifAI;
    QLabel blk[20][20],wht[20][20],txt;
    QFont myfont;
    QPixmap bk,wt;
    QPushButton reset,pvp,pve;
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void endit();
    void topvp();
    void topve();
};

#endif // GOMOKU_H
