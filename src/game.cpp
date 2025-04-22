/**
 * @file game.cpp
 * @author CheDaniSV (chdaprim@gmail.com)
 * @brief Game class, implements game initialization function and main loop function
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game.h"

using namespace std;

Game::Game() {
    int user_input;
    cout << "AWSD to move, x to quit \n" \
        << "1. classic \n" \
        << "2. classic_speedup \n" \
        << "3. nowalls \n" \
        << "4. nowalls_invincible \n" \
        << "~. exit \n" \
        << "Select a game mode: ";
    cin >> user_input;
    clearConsole();
    switch (user_input) {
    case 1:
        vars.gamemode = vars.CLASSIC;
        break;
    case 2:
        vars.gamemode = vars.CLASSIC_SPEEDUP;
        break;
    case 3:
        vars.gamemode = vars.NOWALLS;
        break;
    case 4:
        vars.gamemode = vars.NOWALLS_INVINCIBLE;
        break;
    default:
        vars.isGameOver = true;
        break;
    }
    // Prebaking line of wall
    for (int i = 0; i < vars.width; i++) { 
        vars.wallLine += '#';
    }
    vars.wallLine += '\n';
    // Prebaking empty line
    vars.emptyLine = '#';
    for (int i = 2; i < vars.width; i++) { 
        vars.emptyLine += ' ';
    }
    vars.emptyLine += "#\n";
    // Initial head position
    vars.headX = ceil(vars.playableWidth/2)+1;
    vars.headY = ceil(vars.playableHeight/2)+1;
    // Placing an apple
    place_apple(vars);
}

void Game::tick() {
    system("stty -echo"); // turns off echo, needed for linux
    if (vars.isGameOver)
        exit(0);
    while (!vars.isGameOver) {
        input(vars);
        logic(vars);
        draw(vars);
        sleep_ms(vars.sleepTime);
    }
    system("stty echo");
    results(vars);
    pauseConsole();
    exit(0);
}