#include "checkgameisend.h"

CheckGameIsEnd::CheckGameIsEnd()
{

}

void CheckGameIsEnd::check()
{
    if(gameSatus.gameEnd() != GameVar::NONE)
        emit gameEnd();
}
