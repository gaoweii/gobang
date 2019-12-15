#include "nohands.h"

NoHands::NoHands()
{
    chessboard = getMap();
}
bool NoHands::is_have_nohands()
{
    chessboard = getMap();
    GameVar::Point p(getCurrentPoint().getJ(),getCurrentPoint().getI());
    for(int i = 0; i < 15; i ++)
    {
        for(int j = i; j < 15; j ++)
        {
            int temp = chessboard[i][j];
            chessboard[i][j] = chessboard[j][i];
            chessboard[j][i] = temp;

        }
    }
    int win5 = 0, alive4 = 0, die4 = 0, ddie4 = 0, alive3 = 0,
        dalive3 = 0, die3 = 0, alive2 = 0, dalive2 = 0, die2 = 0, nothing = 0;
    int opp = 1;
    int who = 0;
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
        if(l == 5)
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
    int four = alive4+die4+ddie4;
    int three = dalive3+alive3;
    if((four>=2)||(three>=2))
    {
        return true;
    }
    else {
        return false;
    }
}
