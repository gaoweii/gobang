#ifndef AI_H
#define AI_H
#include "aiinterface.h"
struct dir{
    int dy;
    int dx;
};

const dir d1 = {0, 1};               //横
const dir d2 = {1, 0};               //竖
const dir d3 = {1, -1};              //撇
const dir d4 = {1, 1};               //捺

class AI : public AIinterface
{
public:
    vector<vector<int>> chessboard;

    AI();
    curPoint getCurrentChessDownPoint();
    int score(GameVar::Point p, int who);
    GameVar::Point newPoint (GameVar::Point p, dir d, int lenth){
        GameVar::Point p1(p.getI() + d.dy * lenth, p.getJ() + d.dx * lenth);
        return p1;
    }
    bool isInBoard(GameVar::Point p)
    {
        return p.getI()<15 && p.getJ()<15 && p.getI()>=0 && p.getJ()>=0;
    }

};

#endif // AI_H
