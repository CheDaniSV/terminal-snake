/**
 * @file render.cpp
 * @author CheDaniSV (chdaprim@gmail.com)
 * @brief GameRender class, implements functions to "render" the game to console
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "render.h"

using namespace std;

// Yes, I know, it has almost no effect :)
void GameRender::prebakeLines(GameVariables &vars) {
    // Prebaking wall line
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
}

void GameRender::draw(GameVariables &vars) {
    // Frame buffer
    ostringstream buffer;

    // Top wall
    buffer << vars.wallLine;

    // Side walls and map
    bool isLineNotEmpty = false;
    for (int i = 1; i < vars.height-1; i++) {
        if (vars.fruitY != i && vars.headY != i) {
            for (int j = 0; j < vars.tailLength; j++) {
                if (vars.tailY[j] == i) {
                    isLineNotEmpty = true;
                    break;
                }
            }
        } else {
            isLineNotEmpty = true;
        }
        if (isLineNotEmpty) {
            for (int j = 0; j < vars.width; j++) {
                if (j == 0 || j == vars.width-1)
                    buffer << '#';
                else if (i == vars.headY && j == vars.headX)
                    buffer << "\x1b[32mO\x1b[0m";
                else if (i == vars.fruitY && j == vars.fruitX)
                    buffer << "\x1b[31ma\x1b[0m";
                else {
                    bool print = false;
                    for (int k = 0; k < vars.tailLength; k++) {
                        if (vars.tailX[k] == j && vars.tailY[k] == i) {
                            buffer << "\x1b[32mo\x1b[0m";
                            print = true;
                            break;
                        }
                    }
                    if (!print)
                        buffer << ' ';
                }
            }
            buffer << '\n';
        } else {
            buffer << vars.emptyLine;
        }
    }

    // Bottom wall
    buffer << vars.wallLine;
    buffer << "Score: " << vars.score << '\n';
    if (vars.gamemode == vars.CLASSIC_SPEEDUP) {
        buffer << "Speed: " << 1000./vars.sleepTime;
        if (vars.sleepTime <= vars.minSpeedUpTime)
            buffer << " MAX";
        buffer << '\n';
    }
    if (vars.isDebugMode)
        buffer << "DEBUG: \n" 
            << "fruit: (" << vars.fruitX << ", " << vars.fruitY << ") head: (" << vars.headX << ',' << vars.headY << ") tailLength: " << vars.tailLength << "     \n" \
            << "sleepTime: " << vars.sleepTime << " ms fps: " << 1000./vars.sleepTime << "     \n" \
            << "gridSize: (" << vars.width << 'x' << vars.height << ") gm: " << vars.gamemode << "     \n";

    cout << "\x1b[H" << buffer.str(); // Clear frame and print new one
}

void GameRender::results(GameVariables &vars) {
    cout << "\x1b[2J\x1b[H";
    if (vars.isWin) {
        cout << "\x1b[32m=====Congratulations! You've beat the game!=====\x1b[0m\n";
        cout << "Final score: " << vars.score << '\n';
        cout << "Size of your map was: " << vars.playableWidth << "x" << vars.playableHeight << '\n';
        cout << "And you've achived maximum possible length of the snake for this size: " << vars.maxScore << '\n';
        cout << "\x1b[32mThanks for playing \x1b[31m<3\x1b[0m";
    } else {
        cout << "\x1b[31m=====Game Over=====\x1b[0m\n";
        cout << "Final score: " << vars.score << '\n';
    }
}