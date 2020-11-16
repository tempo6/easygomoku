#include"gomoku.h"


void mygomokuAI::clear()
{
    for(int i=1;i<=15;i++) for(int j=1;j<=15;j++) board[i][j]=0;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

Point mygomokuAI::step(Point p)
{
    int x=p.x,y=p.y,opp=3-me;
    board[x][y]=opp;
    //qDebug("%d %d %d %d\n",x,y,opp,blank(x,y));
    Point q = move();
    board[q.x][q.y]=me;
    return q;
}

bool mygomokuAI::legal(Point p)
{
    return (p.x>0&&p.y>0&&p.x<16&&p.y<16);
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

int mygomokuAI::evaluate(int x, int y, int color, int v) {
    int value = 0;
    int cnt = 0;

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
                            if(v != color)
                            {
                                value += 300000 / 2;
                                cnt++;
                            }
                            else value += 50000000;
                        }
                        else if (board[x + dir[i][0] * 5][y + dir[i][1] * 5] == 3 - color) {
                            //死四 A*11112
                            if(v != color)
                            {
                                value += 2600;
                                cnt++;
                            }
                            else value += 50000000;
                        }

                    }
                    else if (board[x + dir[i][0] * (-1)][y + dir[i][1] * (-1)] == color) {
                        //死四B 1*111
                        if(v != color)
                        {
                            value += 3100;
                            cnt++;
                        }
                        else value += 50000000;
                    }
                }
                else if (board[x + dir[i][0] * (-1)][y + dir[i][1] * (-1)] == color &&
                    board[x + dir[i][0] * (-2)][y + dir[i][1] * (-2)] == color) {
                    //死四C 11*11
                    if(v != color)
                    {
                        value += 2700;
                        cnt++;
                    }
                    else value += 50000000;
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
                        if(v != color) value += 3000 / 2;
                        else value += 300000 / 2;
                        cnt++;
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
    if(cnt>1) value+=300000/2;
    return value;
}

int mygomokuAI::check(int v) {
    int sum1 = 0, sum2 = 0;

    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j <= 15; j++) {
            if (board[i][j] == 0) {
                sum1 += evaluate(i, j, me, v);
                sum2 += evaluate(i, j, 3-me, v);
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
                            sum1 += 50000000;
                        }
                        else if (board[i][j] == 3-me) {
                            sum2 += 50000000;
                        }
                    }
                }
            }
        }
    }
    return Value_Me * sum1 - Value_Enemy * sum2;
}

int mygomokuAI::min_max(int v, int dep, int a, int b)
{
    if(isWin(v))
    {
        if(v == me) return Inf;
        else return -Inf;
    }
    if(isWin(3-v))
    {
        if(v == me) return -Inf;
        else return Inf;
    }
    if(!dep) return check(v);
    int tmp;
    Point_With_Score P;
    vector<Point_With_Score> Q;
    for (int i = 1; i <= 15; i++) for (int j = 1; j <= 15; j++) if (blank(i, j))
    {
        if ((i == 1 || blank(i - 1, j)) && (j == 1 || blank(i, j - 1)) && (i > 14 || blank(i + 1, j)) && (j > 14 || blank(i, j + 1)) && (i == 1 || j == 1 || blank(i - 1, j - 1)) && (i > 14 || j == 1 || blank(i + 1, j - 1)) && (i == 1 || j > 14 || blank(i - 1, j + 1)) && (i > 14 || j > 14 || blank(i + 1, j + 1))) continue;
        board[i][j]=v;
        P.p.x=i;
        P.p.y=j;
        P.score=evaluate(i,j,v,3-v);
        Q.push_back(P);
        board[i][j]=0;
    }
    sort(Q.begin(),Q.end());
    for(int i=0;i<Q.size();i++)
    {
        P=Q[i];
        board[P.p.x][P.p.y]=v;
        tmp=min_max(3-v,dep-1,a,b);
        board[P.p.x][P.p.y]=0;
        if(v==me) a = max(a,tmp);
        else b = min(b,tmp);
        if(a >= b) break;
    }
    if(v == me) return a;
    else return b;
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
        tmp = min_max(3-me, level, -Inf, Inf);
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
