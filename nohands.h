#ifndef NOHANDS_H
#define NOHANDS_H
#include "ai.h"

class NoHands:public AI
{
public:
    NoHands();
    vector<vector<int>> chessboard;
    bool is_have_nohands();
};

#endif // NOHANDS_H
