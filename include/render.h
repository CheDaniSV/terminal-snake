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

/**
 * @brief Declaration of GameRender class
 * 
 */
class GameRender {
    public:
        /**
        * @brief Renders game field
        * 
        * @param vars 
        */
        void draw(GameVariables &vars);

        /**
         * @brief Outputs results of the game when game has ended
         * 
         * @param vars 
         */
        void results(GameVariables &vars);
};

#endif