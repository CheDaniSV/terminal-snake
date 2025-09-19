/**
 * @file variables.h
 * @author CheDaniSV (chdaprim@gmail.com)
 * @brief Header which implements GameVariables class, with varibles used by game objects
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GAME_VARIABLES
#define GAME_VARIABLES

#include <random>
#include <iostream>

using namespace std;

/**
 * @brief GameVariables class, containts all variables for the game
 * 
 */
class GameVariables {
    public:
        /**
         * @brief Enum of gamemodes
         * 
         */
        enum gameModes {CLASSIC, CLASSIC_SPEEDUP, NOWALLS, NOWALLS_INVINCIBLE};

        /**
         * @brief Enum of possible directions, motion states
         * 
         */
        enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};

        int playableWidth; /*!< width of playable field (excluding walls) */
        int playableHeight;  /*!< height of playable field (excluding walls) */
        int width; /*!< width including walls */
        int height; /*!< height including walls */
        int headX; /*!< x cord of snake's head */
        int headY; /*!< y cord of snake's head */
        int fruitX; /*!< x cord of the apple */
        int fruitY; /*!< y cord of the apple */
        int *tailX; /*!< array of X cords of the snake's tail */
        int *tailY; /*!< array of Y cords of the snake's tail */
        int tailLength = 0; /*!< length of snake's tail */
        int score; /*!< game score (total number of apples eaten) */
        int maxScore; /*!< max score for this size of the field */
        int minSpeedUpTime; /*!< min speed when playing speed-up mode */
        int sleepTime; /*!< default speed (time of sleep in cycle) */
        int speedUpDecrement ; /*!< by how much speed is increased in speed-up gamemodes */
        bool isGameOver; /*!< is game over yet? */
        bool isWin ; /*!< have you won? */
        bool isDebugMode; /*!< top-secret debug mode */
        eDirection dir; /*!< instance of directions enum */
        gameModes gamemode; /*!< instance of gamemodes enum */
        string wallLine; /*!< wall line (line full of #)*/
        string emptyLine; /*!< empty line (when there's no apple or snake) */

        // Random-number generator
        random_device rd; /*!< random_device  to generate numbers */
        mt19937 gen; /*!< mersenne twister with a long period of 219937 – 1 */
        uniform_int_distribution<> distribWidth; /*!< declaration of distribution for width */
        uniform_int_distribution<> distribHeight; /*!< declaration of distribution for height */
};

#endif