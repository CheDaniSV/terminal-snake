/**
 * @file game.h
 * @author CheDaniSV (chdaprim@gmail.com)
 * @brief Header of the GameRender class
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GAME_RENDER
#define GAME_RENDER

#include "variables.h"

class GameRender {
    public:
        void draw(GameVariables &vars);
        void results(GameVariables &vars);
};

#endif