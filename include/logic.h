/**
 * @file game.h
 * @author CheDaniSV (chdaprim@gmail.com)
 * @brief Header of the GameLogic class, implements specific for Linux and Windows game logic functions
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GAME_LOGIC
#define GAME_LOGIC

#include "variables.h"
#include "systemfunctions.h"

/**
 * @brief Declaration of GameLogic class
 * 
 */
class GameLogic {
    public:
        /**
         * @brief Places new apple randomly on the field
         * 
         * @param vars 
         */
        void place_apple(GameVariables &vars);

        /**
         * @brief Handels user's input
         * 
         * @param vars 
         */
        void input(GameVariables &vars);

        /**
         * @brief Moves snake, handles collisions, eating a fruit and etc
         * 
         * @param vars 
         */
        void logic(GameVariables &vars);
};

#endif