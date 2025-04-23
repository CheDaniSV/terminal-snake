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

#ifdef _WIN32
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #define WIN32_LEAN_AND_MEAN
    #include <conio.h>
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
    #define clearConsole() system("cls")
    #define pauseConsole() system("pause")
#elif defined(__linux__)
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
    #include <iostream>
    #define sleep_ms(ms) usleep((ms) * 1500) // 1500 should be 1000 (because usleep takes microseconds), but otherwise it's too fast on linux
    #define clearConsole() system("clear")

        // Function to check if a key has been pressed (like _kbhit())
        inline int _kbhit() {
            struct termios oldt, newt;
            int ch;
            int oldf;

            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
            fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

            ch = getchar();

            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            fcntl(STDIN_FILENO, F_SETFL, oldf);

            if (ch != EOF) {
                ungetc(ch, stdin);
                return 1;
            }

            return 0;
        }

        // Function to get a single character input (like _getch())
        inline int _getch() {
            struct termios oldt, newt;
            int ch;

            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            ch = getchar();

            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return ch;
        }

        // Function to pause console (analog of system(pause) on Windows)
        inline void pauseConsole() {
            std::cout << "Press any key to continue...\n";
            termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);         // get current terminal settings
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);        // disable buffering and echo
            tcsetattr(STDIN_FILENO, TCSANOW, &newt); // apply new settings
            getchar();                               // wait for one character
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings
        }

#endif

#include "variables.h"

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