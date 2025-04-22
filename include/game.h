/**
 * @file game.h
 * @author CheDaniSV (chdaprim@gmail.com)
 * @brief Header of the Game class
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GAME
#define GAME

#include <iostream>
#include "render.h"
#include "logic.h"
#include "variables.h"

class Game: public GameRender, public GameLogic {
    public:
        GameVariables vars;
        Game();
        void tick();
};

#endif