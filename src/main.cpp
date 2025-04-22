/**
 * @file main.cpp
 * @author CheDaniSV (chdaprim@gmail.com)
 * @brief Entry point of the program, creates Game instance and starts it with .tick()
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game.h"

/**
 * @brief Main function, creates instance of the Game and starts .tick()
 * 
 * @return int 
 */
int main() {
    Game snakeGame;
    snakeGame.tick();
    return 0;
}