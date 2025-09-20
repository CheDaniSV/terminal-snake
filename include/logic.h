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

        /**
        * @brief Prebake empty lines & wall lines
        * 
        * @param vars
        */
        void prebakeLines(GameVariables &vars);

        /**
        * @brief Set/Update attributes which are depend on size of the field. Allow to change field size at run-time.
        * 
        */
        void SetSizeDependentValues(GameVariables &vars, int width, int height, bool isFirstInit);
};

#endif