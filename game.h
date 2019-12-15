#ifndef GAME_H
#define GAME_H
#include <vector>
#include <stack>
using namespace std;

namespace GameVar {

    const int INT_MAP_SIZE = 15;
    const size_t SIZE_T_INT_MAP_SIZE = 15;

    enum GameRole {FREE, SPECIFIC, PLAY_WITH_COMPUTER, INTERNET, HAVENOHANDS};
    enum Player {WHITE, BLACK, NONE, PEACE};
    struct Point {//一个map点结构体
        size_t i, j;

        Point() {
            i = 0;
            j = 0;
        }

        Point(int _i, int _j) {
            i = static_cast<size_t>(_i);
            j = static_cast<size_t>(_j);
        }

        int getI() { return static_cast<int>(i); }

        int getJ() { return static_cast<int>(j); }

        void setI(int ii) { i = static_cast<size_t>(ii); }

        void setJ(int jj) { j = static_cast<size_t>(jj); }

        void setI(size_t ii) { i = ii; }

        void setJ(size_t jj) { j = jj; }

        bool operator==(Point tmp) {
            if(this->i == tmp.i && this->j == tmp.j)
                return true;
            return false;
        }
    };
}

class Game {
protected:
    static GameVar::Player currentPlayer;//当前玩家
    static GameVar::Point currentPoint;//当前下的位置
    static int gameStep;//极其重要的变量，不要轻易改动他
    static vector<vector<int>> map;//存储整个棋盘，０为黑棋，１为白棋，２为不可点击，－１为没有下过
    static GameVar::GameRole gameRole;//游戏规则
    static bool gameIsEnd;//顾名思义
    static stack<GameVar::Point> chStack;//该栈用来实现三手交换

public:

    Game();
    void stepAdd();//棋子步数加１,
    bool getMap_i_j_CanClicked(size_t i, size_t j);
    GameVar::Player getCurrentPlayer();
    GameVar::Point getCurrentPoint();
    vector<vector<int>> getMap();
    vector<vector<int>> getMap_2();
    int getMap_i_j(size_t i, size_t j);
    GameVar::GameRole getGameRole();
    bool getGameIsEnd();
    stack<GameVar::Point> getChStack();
    int getGameStep();
};

#endif // GAME_H
