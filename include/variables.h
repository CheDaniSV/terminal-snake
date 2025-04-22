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

class GameVariables {
    public:
        enum gameModes {CLASSIC, CLASSIC_SPEEDUP, NOWALLS, NOWALLS_INVINCIBLE};
        enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};
        const int playableWidth = 33;
        const int playableHeight = 17;
        const int width = playableWidth + 2;
        const int height = playableHeight + 2; // REVISIT THIS
        int headX, headY, fruitX, fruitY;
        int *tailX, *tailY;
        int tailLength = 0, score = 0, maxScore = playableWidth*playableHeight-1, minSpeedUpTime = 10, sleepTime = 70, speedUpDecrement = 2;
        bool isGameOver = false, isWin = false, isDebugMode = false;
        eDirection dir = STOP;
        gameModes gamemode;
        string wallLine, emptyLine;
        // Random-number generator
        random_device rd;
        mt19937 gen;
        uniform_int_distribution<> distribWidth;
        uniform_int_distribution<> distribHeight;
        GameVariables() {
            tailX = new int[width*height];
            tailY = new int[width*height];
            mt19937 gen(rd()); // mersenne twister with a long period of 219937 – 1
            distribWidth = uniform_int_distribution<>(1, playableWidth);
            distribHeight = uniform_int_distribution<>(1, playableHeight);
        }
};

#endif