#include "ai.h"
#include <iostream>
using namespace std;
AI::AI()
{
    chessboard = getMap();//０为黑棋，１为白棋，２为不可点击，－１为没有下过
}
curPoint AI::getCurrentChessDownPoint()
{
    GameVar::Point best1;//进攻点
    GameVar::Point best2;//防御点
    int max_ai_1 = 0;
    int max_human_1 = 0;
    int max_ai_2 = 0;
    int max_human_2 = 0;
    chessboard = getMap();
    for(int i = 0; i < 15; i ++)
    {
        for(int j = i; j < 15; j ++)
        {
            int temp = chessboard[i][j];
            chessboard[i][j] = chessboard[j][i];
            chessboard[j][i] = temp;

        }
    }
        for(int i = 0; i < 15; i ++)
        {
            for(int j = 0; j < 15; j ++)
            {
                if(chessboard[i][j] != -1)
                {
                    continue;
                }
                GameVar::Point cur(i,j);
                int cursocre1 = score(cur, 1);//m1表示当前空点对电脑的分值
                int cursocre2 = score(cur, 0);//m2表示当前空点对人的分值
                if(cursocre1 > max_ai_1)
                {
                    best1 = cur;
                    max_ai_1 = cursocre1;
                    max_human_1 = cursocre2;
                }
                else if(cursocre1 == max_ai_1)
                {
                    if(cursocre2 > max_human_1)
                    {
                        best1 = cur;
                        max_ai_1 = cursocre2;
                    }
                }

                if(cursocre2 > max_human_2)
                {
                    best2 = cur;
                    max_human_2 = cursocre2;
                    max_ai_2 = cursocre1;
                }
                else if(cursocre2 == max_human_2)
                {
                    if(cursocre1 > max_ai_2)
                    {
                        best2 = cur;
                        max_ai_2 = cursocre1;
                    }
                }
            }
        }
        if(max_ai_1 >= max_human_2)
        {
            return best1;
        }
        else
        {
            return best2;
        }
    }

int AI::score(GameVar::Point p, int who)
{
    int win5 = 0, alive4 = 0, die4 = 0, ddie4 = 0, alive3 = 0,
        dalive3 = 0, die3 = 0, alive2 = 0, dalive2 = 0, die2 = 0, nothing = 0;
    int opp;
    if(who == 0)
    {
        opp = 1;
    }
    else
    {
        opp = 0;
    }
    for(int i = 1; i <= 4; i ++)
    {
        dir d;
        switch(i)
        {
        case 1:
            d = d1;
            break;
        case 2:
            d = d2;
            break;
        case 3:
            d = d3;
            break;
        case 4:
            d = d4;
            break;
        }
        int l = 1;
        GameVar::Point le, ri, p1;
        int left[5], right[5];
        p1 = newPoint(p, d, -1);
        le = p;
        while(isInBoard(p1) && chessboard[p1.getI()][p1.getJ()] == who)
        {
            le = p1;
            p1 = newPoint(p1, d, -1);
            l ++;
        }
        p1 = newPoint(p, d, 1);
        ri = p;
        while(isInBoard(p1) && chessboard[p1.getI()][p1.getJ()] == who)
        {
            ri = p1;
            p1 = newPoint(p1, d, 1);
            l ++;
        }
        for(int j = 1; j <= 4; j ++)
        {
            p1 = newPoint(le, d, -j);
            if(isInBoard(p1))
            {
                left[j] = chessboard[p1.getI()][p1.getJ()];
            }
            else
            {
                left[j] = opp;
            }
            p1 = newPoint(ri, d, j);
            if(isInBoard(p1))
            {
                right[j] = chessboard[p1.getI()][p1.getJ()];
            }
            else
            {
                right[j] = opp;
            }
        }
        //具体棋型判断
        if(l >= 5)
        {
            win5 ++;
        }
        else if(l == 4)
        {
            if(left[1] == -1 && right[1] == -1) //alive4
            {
                alive4 ++;
            }
            else if(left[1] == -1 || right[1] == -1) //die4
            {
                die4 ++;
            }
            else //nothing
            {
                nothing ++;
            }
        }
        else if(l == 3)
        {
            if((left[1] == -1 && left[2] == who) || (right[1] == -1 && right[2] == who)) //ddie4
            {
                ddie4 ++;
            }
            else if(left[1] == -1 && right[1] == -1 && (left[2] == -1 || right[2] == -1)) //alive3
            {
                alive3 ++;
            }
            else if((left[1] == -1 && left[2] == -1) || (right[1] == -1 && right[2] == -1)) //die3
            {
                die3 ++;
            }
            else if(left[1] == -1 && right[1] == -1) //die3
            {
                die3 ++;
            }
            else //nothing
            {
                nothing ++;
            }
        }
        else if(l == 2)
        {
            if((left[1] == -1 && left[2] == who && left[3] == who) &&
                    (right[1] == -1 && right[2] == who && right[3] == who)) //die4
            {
                ddie4 ++;
            }
            else if(left[1] == -1 && right[1] == -1 &&
                    ((left[2] == who && left[3] == -1) || (right[2] == who && right[3] == -1))) //dalive3
            {
                dalive3 ++;
            }
            else if((left[1] == -1 && left[3] == -1 && left[2] == who) ||
                    (right[1] == -1 && right[3] == -1 && right[2] == who)) //die3
            {
                die3 ++;
            }
            else if((left[1] == -1 && right[1] == -1) &&
                    (left[2] == who || right[2] == who)) //die3
            {
                die3 ++;
            }
            else if((left[1] == -1 && left[2] == -1 && left[3] == who) ||
                    (right[1] == -1 && right[2] == -1 && right[3] == who)) //die3
            {
                die3 ++;
            }
            else if((left[1] == -1 && right[1] == -1 && right[2] == -1 && right[3] == -1) ||
                    (left[1] == -1 && left[2] == -1 && right[1] == -1 && right[2] == -1) ||
                    (left[1] == -1 && left[2] == -1 && left[3] == -1 && right[1] == -1)) //alive2
            {
                alive2 ++;
            }
            else if((left[1] == -1 && left[2] == -1 && left[3] == -1) ||
                    (right[1] == -1 && right[2] == -1 && right[3] == -1)) //die2
            {
                die2 ++;
            }
            else //nothing
            {
                nothing ++;
            }
        }
        else if(l == 1)
        {
            if((left[1] == -1 && left[2] == who && left[3] == who && left[4] == who) ||
                    (right[1] == -1 && right[2] == who && right[3] == who && right[4] == who)) //ddie4
            {
                ddie4 ++;
            }
            else if((left[1] == -1 && right[1] == -1) && ((left[2] == who && left[3] == who && left[4] == -1) ||
                    (right[2] == who && right[3] == who && right[4] == -1))) //dalive3
            {
                dalive3 ++;
            }
            else if((left[1] == -1 && right[1] == -1) &&
                    ((left[2] == who && left[3] == who) || (right[2] == who && right[3] == who))) //die3
            {
                die3 ++;
            }
            else if((left[1] == -1 && left[4] == -1 && left[2] == who && left[3] == who) ||
                    (right[1] == -1 && right[4] == -1 && right[2] == who && right[3] == who)) //die3
            {
                die3 ++;
            }
            else if((left[1] == -1 && left[2] == -1 && left[3] == who && left[4] == who) ||
                    (right[1] == -1 && right[2] == -1 && right[3] == who && right[4] == who)) //die3
            {
                die3 ++;
            }
            else if((left[1] == -1 && left[3] == -1 && left[2] == who && left[4] == who) ||
                    (right[1] == -1 && right[3] == -1 && right[2] == who && right[4] == who)) //die3
            {
                die3 ++;
            }
            else if((left[1] == -1 && right[1] == -1 && right[3] == -1 && right[2] == who) && (left[2] == 0 || right[4] == 0)) //dalive2
            {
                dalive2 ++;
            }
            else if((right[1] == -1 && left[1] == -1 && left[3] == -1 && left[2] == who) &&
                    (right[2] == -1 || left[4] == -1)) //dalive2
            {
                dalive2 ++;
            }
            else if((left[1] == -1 && right[1] == -1 && right[2] == -1 && right[4] == -1 && right[3] == who) ||
                    (right[1] == -1 && left[1] == -1 && left[2] == -1 && left[4] == -1 && left[3] == who)) //dalive2
            {
                dalive2 ++;
            }
            else if((left[1] == -1 && left[3] == -1 && left[4] == -1 && left[2] == who) ||
                    (right[1] == -1 && right[3] == -1 && right[4] == -1 && right[2] == who)) //die2
            {
                die2 ++;
            }
            else if((left[1] == -1 && right[1] == -1 && right[2] == -1 && left[2] == who) ||
                    (right[1] == -1 && left[1] == -1 && left[2] == -1 && right[2] == who)) //die2
            {
                die2 ++;
            }
            else if((left[1] == -1 && left[2] == -1 && left[4] == -1 && left[3] == who) ||
                    (right[1] == -1 && right[2] == -1 && right[4] == -1 && right[3] == who)) //die2
            {
                die2 ++;
            }
            else if((left[1] == -1 && left[2] == -1 && right[1] == -1 && left[3] == who) ||
                    (right[1] == -1 && right[2] == -1 && left[1] == -1 && right[3] == who)) //die2
            {
                die2 ++;
            }
            else if((left[1] == -1 && left[2] == -1 && left[3] == -1 && left[4] == who) ||
                    (right[1] == -1 && right[2] == -1 && right[3] == -1 && right[4] == who)) //die2
            {
                die2 ++;
            }
            else //nothing
            {
                nothing ++;
            }
        }
    }
    if (win5 >= 1)
        return 14;//赢5

    if (alive4 >= 1 || die4 >= 2 || (die4 >= 1 && alive3 >= 1))
        return 13;//活4 双死4 死4活3

    if (alive3 >= 2)
        return 12;//双活3

    if (die3 >= 1 && alive3 >= 1)
        return 11;//死3高级活3

    if (die4 >= 1)
        return 10;//高级死4

    if (ddie4 >= 1)
        return 9;//低级死4

    if (alive3 >= 1)
        return 8;//单活3

    if (dalive3 >= 1)
        return 7;//跳活3

    if (alive2 >= 2)
        return 6;//双活2

    if (alive2 >= 1)
        return 5;//活2

    if (dalive2 >= 1)
        return 4;//低级活2

    if (die3 >= 1)
        return 3;//死3

    if (die2 >= 1)
        return 2;//死2

    return 1;//没有威胁
}

