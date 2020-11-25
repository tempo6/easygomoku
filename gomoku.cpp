#include<gomoku.h>
#define msx (event->x()/40+1)
#define msy (event->y()-200)/40+1

void gomoku::clear()
{
    for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) board[i][j]=0;
    now=end=0;
}

void gomoku::step(Point p)
{
    int x=p.x,y=p.y;
    if(this->board[x][y]) return ;
    board[x][y]=now+1;now^=1;
    check(p);
}

bool gomoku::lft(Point p)
{
    int x=p.x,y=p.y;
    if(board[x-4][y]==board[x-3][y]&&board[x-3][y]==board[x-2][y]&&board[x-2][y]==board[x-1][y]&&board[x-1][y]==board[x][y]) return true;
    return false;
}

bool gomoku::up(Point p)
{
    int x=p.x,y=p.y;
    if(board[x][y-4]==board[x][y-3]&&board[x][y-3]==board[x][y-2]&&board[x][y-2]==board[x][y-1]&&board[x][y-1]==board[x][y]) return true;
    return false;
}

bool gomoku::zs(Point p)
{
    int x=p.x,y=p.y;
    if(board[x-4][y-4]==board[x-3][y-3]&&board[x-3][y-3]==board[x-2][y-2]&&board[x-2][y-2]==board[x-1][y-1]&&board[x-1][y-1]==board[x][y])
      return true;
    return false;
}

bool gomoku::zx(Point p)
{
    int x=p.x,y=p.y;
    if(board[x-4][y+4]==board[x-3][y+3]&&board[x-3][y+3]==board[x-2][y+2]&&board[x-2][y+2]==board[x-1][y+1]&&board[x-1][y+1]==board[x][y])
      return true;
    return false;
}

bool gomoku::legal(Point p)
{
    return (p.x>0&&p.y>0&&p.x<16&&p.y<16);
}

void gomoku::check(Point p)
{
    int x=p.x,y=p.y;
    for(int i=0;i<5;i++) if(legal(p+fx[0]*i)&&legal(p-fx[0]*(4-i))) if(lft(p+fx[0]*i)){win(board[x][y]);return ;}
    for(int i=0;i<5;i++) if(legal(p+fx[6]*i)&&legal(p-fx[6]*(4-i))) if(up(p+fx[6]*i)){win(board[x][y]);return ;}
    for(int i=0;i<5;i++) if(legal(p+fx[7]*i)&&legal(p-fx[7]*(4-i))) if(zs(p+fx[7]*i)){win(board[x][y]);return ;}
    for(int i=0;i<5;i++) if(legal(p+fx[1]*i)&&legal(p-fx[1]*(4-i))) if(zx(p+fx[1]*i)){win(board[x][y]);return ;}
}

void gomoku::win(int who)
{
    end=1;winner=who;
}

bool gomoku::played(Point p)
{
    int x=p.x,y=p.y;
    if(board[x][y]) return true;
    return false;
}

int gomoku::player()
{
    return now+1;
}

bool gomoku::ifwin()
{
    if(end) return true;
    return false;
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

void mywin::clear()
{
    who=1;
    game.clear();AI.clear();
    this->repaint();
    for(int i=1;i<=15;i++) for(int j=1;j<=15;j++)
    {
       blk[i][j].hide();wht[i][j].hide();
    }
    txt.hide();
    end=0;
    if(ifFst)
    {
        AI.setwho(1);
        game.step((Point){8,8});
        blk[8][8].show();
        who=2;
    }
    else AI.setwho(2);
    AI.setlevel(AILevel);
    this->show();
}

void mywin::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen mypen;
    mypen.setWidth(1);
    mypen.setColor(Qt::black);
    painter.setPen(mypen);
    for(int i=1;i<=15;i++) painter.drawLine(20,220+40*(i-1),580,220+40*(i-1));
    for(int j=1;j<=15;j++) painter.drawLine(20+40*(j-1),220,20+40*(j-1),780);
    mypen.setWidth(5);
    painter.setPen(mypen);
    painter.drawPoint(300,500);
    painter.drawPoint(140,340);painter.drawPoint(460,340);
    painter.drawPoint(140,660);painter.drawPoint(460,660);
}

void mywin::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    if(event->button()==Qt::LeftButton&&event->y()>=200&&!end)
    {
      //qDebug("%d %d\n",event->x(),event->y());
      Point p={msx,msy},q;
      if(!game.played(p))
      {
        game.step(p);
        if(who==1) blk[msx][msy].show();
        else wht[msx][msy].show();
        who=game.player();
      }
      if(game.ifwin()) endit();
      //qDebug("%d\n",who);
      if(ifAI&&!end&&who==2-ifFst)
      {
        txt.setText("AI思考中……");
        txt.show();
        q=AI.step(p);
        game.step(q);
        if(who==1) blk[q.x][q.y].show();
        else wht[q.x][q.y].show();
        who=game.player();
        txt.hide();
      }
      //qDebug("%d\n",who);
      if(game.ifwin()) endit();
      //qDebug("%d\n",game.ifwin());
    }
}

void mywin::topve()
{
    ifAI=1;
    clear();
    lev.show();
    fst.show();
}

void mywin::topvp()
{
    ifAI=0;
    clear();
    lev.hide();
    fst.hide();
}

void mywin::endit()
{
    end=1;
    if(who==1) txt.setText("白棋获胜！");
    else txt.setText("黑棋获胜！");
    txt.show();
}

void mywin::setLev(int v)
{
    AILevel=v;
    ifAI=1;
    clear();
}

void mywin::setfst(int v)
{
    if(v==0) ifFst=0;
    else ifFst=1;
    clear();
}
