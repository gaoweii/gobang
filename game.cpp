#include "game.h"

GameVar::Player Game::currentPlayer = GameVar::BLACK;
GameVar::GameRole Game::gameRole = GameVar::FREE;
GameVar::Point Game::currentPoint;
vector<vector<int>> Game::map;
int Game::gameStep = 0;
bool Game::gameIsEnd = false;
stack<GameVar::Point> Game::chStack;


Game::Game() {
    for(int i = 0; i < 15; ++i) {
        map.push_back(vector<int>(15, -1));
    }
}

vector<vector<int>> Game::getMap() {
    return map;
}

vector<vector<int> > Game::getMap_2()
{
    vector<vector<int>> _map;
    for(size_t j = 0; j < GameVar::SIZE_T_INT_MAP_SIZE; ++j) {
        _map.push_back(vector<int>(GameVar::SIZE_T_INT_MAP_SIZE, -1));
        for(size_t i = 0; i < GameVar::SIZE_T_INT_MAP_SIZE; ++i) {
            _map[i][j] = map[j][i];
        }
    }
    return _map;
}

void Game::stepAdd() {
    gameStep++;
    if(gameStep % 2 == 0) {
        currentPlayer = GameVar::WHITE;
    } else {
        currentPlayer = GameVar::BLACK;
    }
}

bool Game::getMap_i_j_CanClicked(size_t i, size_t j)//返回i,j可否点击
{
    if(map[i][j] != -1) {
        return false;
    }
    else return true;
}

GameVar::GameRole Game::getGameRole() {
    return gameRole;
}

GameVar::Player Game::getCurrentPlayer() {
    if(gameRole == GameVar::SPECIFIC && gameStep == 6) {
        currentPlayer = GameVar::BLACK;
        return currentPlayer;
    }
//    if(gameStep % 2 == 0)
//        currentPlayer = GameVar::WHITE;
//    else
//        currentPlayer = GameVar::BLACK;
    return currentPlayer;
}

int Game::getMap_i_j(size_t i, size_t j) {
    return map[i][j];
}

GameVar::Point Game::getCurrentPoint() {
    return currentPoint;
}

bool Game::getGameIsEnd() { return gameIsEnd; }

stack<GameVar::Point> Game::getChStack()
{
    return chStack;
}

int Game::getGameStep()
{
   return gameStep;
}
