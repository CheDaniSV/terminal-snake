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
         * @brief Enum of possible directions, motions states
         * 
         */
        enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};

        const int playableWidth = 33; /*!< width of playable field (excluding walls) */
        const int playableHeight = 17;  /*!< height of playable field (excluding walls) */
        const int width = playableWidth + 2; /*!< width including walls */
        const int height = playableHeight + 2; /*!< height including walls */
        int headX; /*!< x cord of snake's head */
        int headY; /*!< y cord of snake's head */
        int fruitX; /*!< x cord of the apple */
        int fruitY; /*!< y cord of the apple */
        int *tailX; /*!< array of X cords of the snake's tail */
        int *tailY; /*!< array of Y cords of the snake's tail */
        int tailLength = 0; /*!< length of snake's tail */
        int score = 0; /*!< game score (total number of apples eaten) */
        int maxScore = playableWidth*playableHeight-1; /*!< max score for this size of the field */
        int minSpeedUpTime = 10; /*!< min speed when playing speed-up mode */
        int sleepTime = 70; /*!< default speed (time of sleep in cycle) */
        int speedUpDecrement = 2; /*!< by how much speed is increased in speed-up gamemodes */
        bool isGameOver = false; /*!< is game over yet? */
        bool isWin = false; /*!< have you won? */
        bool isDebugMode = false; /*!< top-secret debug mode */
        eDirection dir = STOP; /*!< instance of directions enum */
        gameModes gamemode; /*!< instance of gamemodes enum */
        string wallLine; /*!< wall line (line full of #)*/
        string emptyLine; /*!< empty line (when there's no apple or snake) */

        // Random-number generator
        random_device rd; /*!< random_device  to generate numbers */
        mt19937 gen; /*!< mersenne twister with a long period of 219937 – 1 */
        uniform_int_distribution<> distribWidth; /*!< declaration of distribution for width */
        uniform_int_distribution<> distribHeight; /*!< declaration of distribution for height */
        
        /**
        * @brief Constructor of GameVariables class, initilizes dynamic arrays and random number generators
        * 
        */
        GameVariables() {
            tailX = new int[width*height];
            tailY = new int[width*height];
            mt19937 gen(rd());
            distribWidth = uniform_int_distribution<>(1, playableWidth);
            distribHeight = uniform_int_distribution<>(1, playableHeight);
        }
};

#endif