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

/**
 * @brief Declaration of Game class
 * 
 */
class Game: public GameRender, public GameLogic {
    public:
        GameVariables vars; /*!< instance of game variables (object holding all variables global) */

        /**
        * @brief Constructor of Game, initializes start dialog and other preparations
        * 
        */
        Game();

        /**
        * @brief "Ticker" - Starts main loop of the game
        *
        */
        void tick();
};

#endif