#include "Game.h"


int Game::counter() {
    return amountMines - amountFlags;
}

