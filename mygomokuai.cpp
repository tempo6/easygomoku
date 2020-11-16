#include"gomoku.h"


void mygomokuAI::clear()
{
    for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) board[i][j]=0;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

Point mygomokuAI::step(Point p)
{
    int x=p.x,y=p.y/*,maxn=-1000000000,s=0*/,opp=3-me;
    board[x][y]=opp;
    //qDebug("%d %d %d %d\n",x,y,opp,blank(x,y));
    Point q = move();

    /*Point q;
    vector<Point> ans;
    for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) if(!board[i][j])
    {
       q.x=i;q.y=j;
       s=calval(q,me);
       if(s==maxn) ans.push_back(q);
       if(s>maxn){maxn=s;ans.clear();ans.push_back(q);}
    }

    for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) if(!board[i][j])
    {
        q.x=i;q.y=j;
        s=calval(q,opp);
        if(s==maxn) ans.push_back(q);
        if(s>maxn){maxn=s;ans.clear();ans.push_back(q);}
    }
    for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) if(!board[i][j])
    {
       q.x=i;q.y=j;
       s=searching(q,me,1);
       if(s==maxn) ans.push_back(q);
       if(s>maxn){maxn=s;ans.clear();ans.push_back(q);}
    }
    qDebug("%d %d  %d\n",ans[0].x,ans[0].y,maxn);
    s=qrand()%ans.size();
    q=ans[s];ans.clear();ans.shrink_to_fit();*/
    board[q.x][q.y]=me;

    return q;
}

bool mygomokuAI::legal(Point p)
{
    return (p.x>0&&p.y>0&&p.x<16&&p.y<16);
}

int mygomokuAI::which(Point p)
{
    if(!legal(p)) return 0;
    return board[p.x][p.y];
}

int mygomokuAI::hmy(Point p, int f, int who)
{
    int cnt=0;
    while(legal(p+fx[f]*(cnt+1)))
    {
        if(which(p+fx[f]*(cnt+1))!=who) break;
        cnt++;
    }
    return cnt;
}

bool mygomokuAI::checkfive(Point p,int who)
{
    bool f=0;
    for(int i=0;i<5;i++)
    {
        if(hmy(p,i,who)+hmy(p,i+4,who)>3){f=1;break;}
    }
    return f;
}

bool mygomokuAI::checklivefour(Point p, int who)
{
    bool f=0;
    int l,r;
    for(int i=0;i<5;i++)
    {
       l=hmy(p,i,who);r=hmy(p,i+4,who);
       if(l+r>2&&which(p+fx[i]*(l+1))==0&&which(p+fx[i+4]*(r+1))==0){f=1;break;}
    }
    return f;
}

int mygomokuAI::checkdeadfour(Point p, int who)
{
    int cnt=0;
    int l,r,opp=3-who;
    for(int i=0;i<5;i++)
    {
       l=hmy(p,i,who);r=hmy(p,i+4,who);
       if(l+r>2&&((which(p+fx[i]*(l+1))==opp&&which(p+fx[i+4]*(r+1))==0)||(which(p+fx[i]*(l+1))==0&&which(p+fx[i+4]*(r+1))==opp))){cnt++;continue;}
       if(l+r+hmy(p+fx[i]*(l+1),i,who)>3){cnt++;continue;}
       if(l+r+hmy(p+fx[i+4]*(r+1),i+4,who)>3){cnt++;continue;}
    }
    return cnt;
}

int mygomokuAI::checklivethree(Point p, int who)
{
    int cnt=0;
    int l,r,ll,rr;
    for(int i=0;i<5;i++)
    {
       l=hmy(p,i,who);r=hmy(p,i+4,who);
       ll=hmy(p+fx[i]*(l+1),i,who);rr=hmy(p+fx[i+4]*(r+1),i+4,who);
       if(l+r>1&&which(p+fx[i]*(l+1))==0&&which(p+fx[i+4]*(r+1))==0){cnt++;continue;}
       if(ll&&l+r+ll>1&&which(p+fx[i+4]*(r+1))==0&&which(p+fx[i]*(l+ll+2))==0&&which(p+fx[i]*(l+1))==0){cnt++;continue;}
       if(rr&&l+r+rr>1&&which(p+fx[i]*(l+1))==0&&which(p+fx[i+4]*(r+rr+2))==0&&which(p+fx[i+4]*(r+1))==0){cnt++;continue;}
    }
    return cnt;
}

bool mygomokuAI::checkdeadthree(Point p, int who)
{
    bool f=0;
    int l,r,ll,rr,opp=3-who;
    for(int i=0;i<5;i++)
    {
       l=hmy(p,i,who);r=hmy(p,i+4,who);
       ll=hmy(p+fx[i]*(l+1),i,who);rr=hmy(p+fx[i+4]*(r+1),i+4,who);
       if(ll&&l+r+ll>1&&((which(p+fx[i]*(l+1))==0&&which(p+fx[i]*(l+ll+2))==opp&&which(p+fx[i+4]*(r+1))==0)||(which(p+fx[i]*(l+1))==0&&which(p+fx[i]*(l+ll+2))==0&&which(p+fx[i+4]*(r+1))==opp)))
       {f=1;break;}
       if(rr&&l+r+rr>1&&((which(p+fx[i+4]*(r+1))==0&&which(p+fx[i]*(l+1))==opp&&which(p+fx[i+4]*(r+rr+2))==0)||(which(p+fx[i+4]*(r+1))==0&&which(p+fx[i]*(l+1))==0&&which(p+fx[i+4]*(r+rr+2))==opp)))
       {f=1;break;}
       if(l+r>1&&l+r<3&&which(p+fx[i]*(l+2))==opp&&which(p+fx[i+4]*(r+2))==opp&&which(p+fx[i]*(l+1))==0&&which(p+fx[i+4]*(r+1))==0){f=1;break;}
    }
    return f;
}

bool mygomokuAI::checklivetwo(Point p, int who)
{
    bool f=0;
    int l,r,ll,rr;
    for(int i=0;i<5;i++)
    {
       l=hmy(p,i,who);r=hmy(p,i+4,who);
       ll=hmy(p+fx[i]*(l+1),i,who);rr=hmy(p+fx[i+4]*(r+1),i+4,who);
       if(l+r>0&&which(p+fx[i]*(l+1))==0&&which(p+fx[i+4]*(r+1))==0){f=1;break;}
       if(ll&&l+r+ll>0&&which(p+fx[i]*(l+1))==0&&which(p+fx[i]*(l+ll+2))==0&&which(p+fx[i+4]*(r+1))==0){f=1;break;}
       if(ll&&l+r+rr>0&&which(p+fx[i+4]*(r+1))==0&&which(p+fx[i]*(l+1))==0&&which(p+fx[i+4]*(r+rr+2))==0){f=1;break;}
    }
    return f;
}

bool mygomokuAI::checkdeadtwo(Point p, int who)
{
    bool f=0;
    int l,r,ll,rr,opp=3-who;
    for(int i=0;i<5;i++)
    {
       l=hmy(p,i,who);r=hmy(p,i+4,who);
       ll=hmy(p+fx[i]*(l+1),i,who);rr=hmy(p+fx[i+4]*(r+1),i+4,who);
       if(l+r>0&&which(p+fx[i]*(l+1))+which(p+fx[i+4]*(r+1))==opp){f=1;break;}
       if(ll&&l+r+ll>0&&which(p+fx[i]*(l+1))==0&&which(p+fx[i]*(l+ll+2))+which(p+fx[i+4]*(r+1))==opp){f=1;break;}
       if(ll&&l+r+rr>0&&which(p+fx[i+4]*(r+1))==0&&which(p+fx[i]*(l+1))+which(p+fx[i+4]*(r+rr+2))==opp){f=1;break;}
    }
    return f;
}

int mygomokuAI::calval(Point p, int who)
{
    int val=0;
    if(checkfive(p,who)) val+=100000000;
    if(checklivefour(p,who)||checkdeadfour(p,who)>1) val+=2000000;
    if(checklivethree(p,who)>1) val+=1000000;
    if(checklivethree(p,who)==1) val+=100000;
    if(checklivetwo(p,who)) val+=500;
    if(checkdeadfour(p,who)==1){val+=200;if(checklivethree(p,who)) val+=2000000;}
    if(checkdeadthree(p,who)) val+=150;
    if(checkdeadtwo(p,who)) val+=100;
    for(int i=0;i<8;i++) if(legal(p+fx[i])&&which(p+fx[i])!=0) val+=(qrand()%2)*10;
    return val;
}

void mygomokuAI::setlevel(int x)
{
    level=x;
}

void mygomokuAI::setwho(int x)
{
    me=x;
    if(x==1)
    {
        Value_Me=3;
        Value_Enemy=2;
    }
    else
    {
        Value_Enemy=3;
        Value_Me=2;
    }
}

int mygomokuAI::searching(Point p, int who, int depth)
{
    int opp=3-who,val;
    board[p.x][p.y]=who;
    if(depth>level)
    {
      Point q;
      val=0;
      int maxn=-1000000000,minn=-1000000000;
      for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) if(board[i][j]==me)
      {
          q.x=i;q.y=j;
          maxn=max(maxn,calval(q,me));
      }
      for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) if(board[i][j]==3-me)
      {
          q.x=i;q.y=j;
          minn=max(minn,calval(q,3-me));
      }
      board[p.x][p.y]=0;val=maxn-minn;
      return val;
    }
    if(who==me) val=-1000000000;else val=1000000000;
    for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) if(!board[i][j]&&(calval({i,j},who)>100||calval({i,j},opp)>100))
    {
        if(who==me) val=max(val,searching({i,j},opp,depth+1));
        else val=min(val,searching({i,j},opp,depth+1));
    }
    board[p.x][p.y]=0;
    return val;
}

//0:空位，1:己方棋子，2:对方棋子，*:当前空位
int mygomokuAI::evaluate(int x, int y, int color) {
    int value = 0;
    //	int numoftwo = 0;

    for (int i = 1; i <= 8; i++) {

        if (board[x + dir[i][0] * 1][y + dir[i][1] * 1] == color) {
            //*1
            if (board[x + dir[i][0] * 2][y + dir[i][1] * 2] == color) {
                //*11
                if (board[x + dir[i][0] * 3][y + dir[i][1] * 3] == color) {
                    //*111
                    if (board[x + dir[i][0] * 4][y + dir[i][1] * 4] == color) {
                        //*1111
                        if (board[x + dir[i][0] * 5][y + dir[i][1] * 5] == 0) {
                            //活四 *11110
                            value += 300000 / 2;
                        }
                        else if (board[x + dir[i][0] * 5][y + dir[i][1] * 5] == 3 - color) {
                            //死四 A*11112

                            value += 2600;
                        }

                    }
                    else if (board[x + dir[i][0] * (-1)][y + dir[i][1] * (-1)] == color) {
                        //死四B 1*111
                        value += 3100;
                    }
                }
                else if (board[x + dir[i][0] * (-1)][y + dir[i][1] * (-1)] == color &&
                    board[x + dir[i][0] * (-2)][y + dir[i][1] * (-2)] == color) {
                    //死四C 11*11
                    value += 2700;
                }
                else if (board[x + dir[i][0] * 3][y + dir[i][1] * 3] == 0 &&
                    board[x + dir[i][0] * 4][y + dir[i][1] * 4] == color &&
                    board[x + dir[i][0] * 5][y + dir[i][1] * 5] == 0) {
                    //死三B *11010
                    value += 800;
                }
            }
            else if (board[x + dir[i][0] * 1][y + dir[i][1] * 1] == 0) {
                //*10
                if (board[x + dir[i][0] * 3][y + dir[i][1] * 3] == color &&
                    board[x + dir[i][0] * (-1)][y + dir[i][1] * (-1)] == color) {
                    //死三D 1*101
                    value += 550 / 2;
                }
                else if (board[x + dir[i][0] * 3][y + dir[i][1] * 3] == 0 &&
                    board[x + dir[i][0] * 4][y + dir[i][1] * 4] == color &&
                    board[x + dir[i][0] * 5][y + dir[i][1] * 5] == 0) {
                    //死二C *10010
                    value += 200 / 2;
                }
            }
        }
        else if (board[x + dir[i][0] * 1][y + dir[i][1] * 1] == 0) {
            //*0
            if (board[x + dir[i][0] * 2][y + dir[i][1] * 2] == color) {
                //*01
                if (board[x + dir[i][0] * 3][y + dir[i][1] * 3] == color &&
                    board[x + dir[i][0] * 4][y + dir[i][1] * 4] == color) {
                    //*0111
                    if (board[x + dir[i][0] * 5][y + dir[i][1] * 5] == 0 &&
                        board[x + dir[i][0] * 6][y + dir[i][1] * 6] == 0) {
                        //活三 *011100
                        value += 3000 / 2;
                    }
                    else if (board[x + dir[i][0] * 5][y + dir[i][1] * 5] == 3 - color) {
                        //死三A *01112
                        value += 500;
                    }
                }
                else if (board[x + dir[i][0] * (-1)][y + dir[i][1] * (-1)] == color &&
                    board[x + dir[i][0] * (-2)][y + dir[i][1] * (-2)] == color) {
                    //死三C 11*01
                    value += 600;
                }
                else if (board[x + dir[i][0] * 3][y + dir[i][1] * 3] == 0 &&
                    board[x + dir[i][0] * 4][y + dir[i][1] * 4] == color &&
                    board[x + dir[i][0] * 5][y + dir[i][1] * 5] == 0 &&
                    board[x + dir[i][0] * 6][y + dir[i][1] * 6] == 0) {
                    //死二B *010100
                    value += 250 / 2;
                }
            }
            else if (board[x + dir[i][0] * 2][y + dir[i][1] * 2] == 0) {
                //*00
                if (board[x + dir[i][0] * 3][y + dir[i][1] * 3] == color &&
                    board[x + dir[i][0] * 4][y + dir[i][1] * 4] == color) {
                    //*0011
                    if (board[x + dir[i][0] * 5][y + dir[i][1] * 5] == 0 &&
                        board[x + dir[i][0] * 6][y + dir[i][1] * 6] == 0 &&
                        board[x + dir[i][0] * 7][y + dir[i][1] * 7] == 0) {
                        //活二 *0011000
                        value += 650 / 2;
                    }
                    else if (board[x + dir[i][0] * 5][y + dir[i][1] * 5] == 3 - color) {
                        //死二A *00112
                        value += 150;
                    }
                }
            }
        }
    }
    return value;
}

int mygomokuAI::check() {
    int sum1 = 0, sum2 = 0;

    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j <= 15; j++) {
            if (board[i][j] == 0) {
                sum1 += evaluate(i, j, me);
                sum2 += evaluate(i, j, 3-me);
            }
            else {
                //五子
                for (int k = 1; k <= 4; k++) {
                    if ((i + dir[k][0] * 4 > 0 && i + dir[k][0] * 4 < 16 && j + dir[k][1] * 4 > 0 && j + dir[k][1] * 4 < 16) &&
                        board[i][j] == board[i + dir[k][0] * 1][j + dir[k][1] * 1] &&
                        board[i][j] == board[i + dir[k][0] * 2][j + dir[k][1] * 2] &&
                        board[i][j] == board[i + dir[k][0] * 3][j + dir[k][1] * 3] &&
                        board[i][j] == board[i + dir[k][0] * 4][j + dir[k][1] * 4]) {
                        if (board[i][j] == me) {
                            sum1 += 5000000;
                        }
                        else if (board[i][j] == 3-me) {
                            sum2 += 5000000;
                        }
                    }
                }
            }
        }
    }
//	cout << sum1 << ' ' << sum2 << endl;
    return Value_Me * sum1 - Value_Enemy * sum2;
}

int mygomokuAI::min_max(int v, int dep, int ab)
{
    if (isWin(v))
    {
        if (v == me) return 5000000;
        else return -5000000;
    }

    if (!dep) return check();
    int score = -Inf, tmp;



    for (int i = 1; i <= 15; i++) for (int j = 1; j <= 15; j++) if (blank(i, j))
    {
        if ((i == 1 || blank(i - 1, j)) && (j == 1 || blank(i, j - 1)) && (i > 14 || blank(i + 1, j)) && (j > 14 || blank(i, j + 1)) && (i == 1 || j == 1 || blank(i - 1, j - 1)) && (i > 14 || j == 1 || blank(i + 1, j - 1)) && (i == 1 || j > 14 || blank(i - 1, j + 1)) && (i > 14 || j > 14 || blank(i + 1, j + 1))) continue;
        //board->setStone(i, j, v);
        board[i][j]=v;
        tmp = min_max(3 - v, dep - 1, -score);
        if (v != me) tmp = -tmp;
        score = max(score, tmp);
        //board->remove(i, j);
        board[i][j]=0;
        if (score >= ab)
        {
            if (v == me) return score;
            else return -score;
        }
    }
    if (v == me) return score;
    else return -score;
}

bool mygomokuAI::isWin(int v)
{
    for (int i = 1; i <= 15; i++) for (int j = 1; j <= 15; j++) if (board[i][j] == v) {
        for (int k = 1; k <= 8; k++) {
            if (
                legal((Point){i + dir[k][0] * 1,j + dir[k][1] * 1})&&
                board[i + dir[k][0] * 1][j + dir[k][1] * 1] == v &&
                legal((Point){i + dir[k][0] * 2,j + dir[k][1] * 2})&&
                board[i + dir[k][0] * 2][j + dir[k][1] * 2] == v &&
                legal((Point){i + dir[k][0] * 3,j + dir[k][1] * 3})&&
                board[i + dir[k][0] * 3][j + dir[k][1] * 3] == v &&
                legal((Point){i + dir[k][0] * 4,j + dir[k][1] * 4})&&
                board[i + dir[k][0] * 4][j + dir[k][1] * 4] == v) {
                return 1;
            }

        }
    }
    return 0;
}

bool mygomokuAI::blank(int x, int y)
{
    if(board[x][y]==0) return 1;
    return 0;
}

Point mygomokuAI::move()
{
    int score = -Inf - 5, tmp;
    Point s;
    s.x = 8;
    s.y = 8;
    for (int i = 1; i <= 15; i++) for (int j = 1; j <= 15; j++) if (blank(i, j))
    {
        if ((i==1 || blank(i - 1, j)) && (j==1 || blank(i, j - 1)) && (i > 14 || blank(i + 1, j)) && (j > 14 || blank(i, j + 1)) && (i==1 || j==1 || blank(i - 1, j - 1)) && (i > 14 || j==1 || blank(i + 1, j - 1)) && (i==1 || j > 14 || blank(i - 1, j + 1)) && (i > 14 || j > 14 || blank(i + 1, j + 1))) continue;
        //board->setStone(i, j, 1);
        board[i][j]=me;
        tmp = min_max(3-me, level, Inf);
//		printf("(%d，%d)：%d\n", i, j, tmp);
        if (tmp > score)
        {
            score = tmp;
            s.x = i;
            s.y = j;
        }
        //board->remove(i, j);
        board[i][j]=0;
    }
    return s;
}
