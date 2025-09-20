/**
 * @file logic.cpp
 * @author CheDaniSV (chdaprim@gmail.com)
 * @brief GameLogic class, implements functions responsible for game's logic
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "logic.h"

using namespace std;

// Yes, I know, it has almost no effect :)
void GameLogic::prebakeLines(GameVariables &vars) {
    vars.wallLine.clear();
    vars.emptyLine.clear();

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

void GameLogic::SetSizeDependentValues(GameVariables &vars, int width, int height, bool isFirstInit = false) {
    if (width > 3 && height > 3) {
        vars.playableWidth = width - 2;
        vars.playableHeight = height - 2;
        vars.width = width;
        vars.height = height;
        vars.maxScore = vars.playableWidth*vars.playableHeight-1;

        if (!isFirstInit) {
            int *tempTailX = new int[vars.width*vars.height];
            int *tempTailY = new int[vars.width*vars.height];
            int oldTailLength = vars.tailLength;
            int maxTailLength = vars.width * vars.height;
            if (vars.tailX != nullptr && vars.tailY != nullptr) {
                int copyLength = (oldTailLength < maxTailLength) ? oldTailLength : maxTailLength;
                for (int i = 0; i < copyLength; i++) {
                    tempTailX[i] = vars.tailX[i];
                    tempTailY[i] = vars.tailY[i];
                }
                delete[] vars.tailX;
                delete[] vars.tailY;
            }
            vars.tailX = tempTailX;
            vars.tailY = tempTailY;

            // Clamp tailLength to new max possible value
            if (vars.tailLength > maxTailLength) {
                vars.tailLength = maxTailLength;
            }
        } else {
            vars.tailX = new int[vars.width*vars.height];
            vars.tailY = new int[vars.width*vars.height];

            // Clamp tailLength to new max possible value
            if (vars.tailLength > vars.width * vars.height) {
                vars.tailLength = vars.width * vars.height;
            }
        }

        if (vars.score > vars.maxScore)
            vars.score = vars.maxScore - 1;

        if (vars.fruitX <= 0 || vars.fruitX >= width - 1 || vars.fruitY <= 0 || vars.fruitY >= height - 1)
            place_apple(vars);

        vars.gen = mt19937(vars.rd()); // Doesn't need to be here, but anyway
        vars.distribWidth = uniform_int_distribution<>(1, vars.playableWidth);
        vars.distribHeight = uniform_int_distribution<>(1, vars.playableHeight);

        prebakeLines(vars);
        cout << "\x1b[2J\x1b[H";
    }
}

void GameLogic::place_apple(GameVariables &vars) {
    vars.fruitX = vars.distribWidth(vars.gen);
    vars.fruitY = vars.distribHeight(vars.gen);
    if (vars.fruitX == vars.headX && vars.fruitY == vars.headY) {
        place_apple(vars);
        return;
    }
    for (int i = 0; i < vars.tailLength; i++) {
        if (vars.fruitX == vars.tailX[i] && vars.fruitY == vars.tailY[i]) {
            place_apple(vars);
            return;
        }
    }
}

void GameLogic::input(GameVariables &vars) {
    if (_kbhit()) {
        switch (_getch()) {
            case 75:
            case 'a':
                vars.dir = vars.LEFT;
                break;
            case 77:
            case 'd':
                vars.dir = vars.RIGHT;
                break;
            case 72:
            case 'w':
                vars.dir = vars.UP;
                break;
            case 80:
            case 's':
                vars.dir = vars.DOWN;
                break;
            case 'x':
                vars.isGameOver = true;
                break;
            case '`':
                vars.isDebugMode = !vars.isDebugMode;
                clearConsole();
                break;
            case '+':
                if (vars.isDebugMode)
                    vars.tailLength += 2;
                break;
            case '-':
                if (vars.isDebugMode && (vars.tailLength-2) >= 0)
                    vars.tailLength -= 2;
                break;
            case '\'':
                if (vars.isDebugMode)
                    vars.dir = vars.STOP;
                break;
            case ']':
                if (vars.isDebugMode && vars.sleepTime < 150)
                    vars.sleepTime += 10;
                break;
            case '[':
                if (vars.isDebugMode && vars.sleepTime > 0)
                    vars.sleepTime -= 10;
                break;
            case '.':
                SetSizeDependentValues(vars, vars.width + 1, vars.height + 1);
                break;
            case ',':
                SetSizeDependentValues(vars, vars.width - 1, vars.height - 1);
                break;
        }
    }
}

void GameLogic::logic(GameVariables &vars) {
    // Moving tail
    int prevX = vars.tailX[0];
    int prevY = vars.tailY[0];
    int prev2X, prev2Y; // Buffer

    // Move the first part on the previous head's place
    vars.tailX[0] = vars.headX;
    vars.tailY[0] = vars.headY; 

    // Start with 1,ּ as 0 tail part is already moved
    for (int i = 1; i < vars.tailLength; i++) {
        prev2X = vars.tailX[i];
        prev2Y = vars.tailY[i];
        vars.tailX[i] = prevX;
        vars.tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Moving head
    switch (vars.dir) {
        case vars.LEFT:
            vars.headX--;
            break;
        case vars.RIGHT:
            vars.headX++;
            break;
        case vars.UP:
            vars.headY--;
            break;
        case vars.DOWN:
            vars.headY++;
            break;
    }

    // Check for collision with the walls
    switch (vars.gamemode) {
        case vars.CLASSIC:
        case vars.CLASSIC_SPEEDUP:
            if (vars.headX <= 0 || vars.headX >= vars.width - 1 || vars.headY <= 0 || vars.headY >= vars.height - 1)
                vars.isGameOver = true;
            break;
        case vars.NOWALLS:
        case vars.NOWALLS_INVINCIBLE:
            if (vars.headX >= vars.width - 1)
                vars.headX = 1;
            else if (vars.headX <= 0)
                vars.headX = vars.width - 1;
            if (vars.headY >= vars.height - 1)
                vars.headY = 1;
            else if (vars.headY <= 0)
                vars.headY = vars.height - 1;
            break;
    }

    // Check for collision with tail
    if (vars.gamemode != vars.NOWALLS_INVINCIBLE) {
        for (int i = 0; i < vars.tailLength; i++)
            if (vars.tailX[i] == vars.headX && vars.tailY[i] == vars.headY)
                vars.isGameOver = true;
    }

    // Eating a fruit
    if (vars.headX == vars.fruitX && vars.headY == vars.fruitY) {

        vars.score++;

        if (vars.tailLength != vars.maxScore) {
            vars.tailLength++;
        } else {
            vars.isGameOver = true;
            vars.isWin = true;
        }

        place_apple(vars);

        // For speed-up gamemode - speeds up the game
        if (vars.gamemode == vars.CLASSIC_SPEEDUP && (vars.sleepTime - vars.speedUpDecrement) >= vars.minSpeedUpTime)
            vars.sleepTime -= vars.speedUpDecrement;
    }
}