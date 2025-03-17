#include <iostream>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
    #define systemClearScreen() system("cls")
#elif defined(__linux__)
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
    #define sleep_ms(ms) usleep((ms) * 1000)
    #define systemClearScreen() system("clear")
        // Function to check if a key has been pressed (like _kbhit())
        int _kbhit() {
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
        int _getch() {
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
#endif

using namespace std;

enum gameModes {CLASSIC, CLASSIC_SPEEDUP, NOWALLS, NOWALLS_INVINCIBLE};
enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};
const int playableWidth = 40;
const int playableHeight = 20;
const int width = playableWidth + 2;
const int height = playableHeight - 2;
int headX, headY, fruitX, fruitY;
int tailX[width], tailY[height];
int tailLength = 0, score = 0;
int sleepTime = 70;
bool isGameOver = false;
bool forceQuit = false;
bool isDebugMode = false;
eDirection dir = STOP;
gameModes gamemode;
string wallLine, emptyLine;

void place_apple() {
    fruitX = 1 + rand() % playableWidth;
    fruitY = rand() % height;
    if (fruitX == headX && fruitY == headY) {
        place_apple();
        return;
    }
    if (fruitX < 1 || fruitX > playableWidth || fruitY < 0 || fruitX > playableHeight) {
        place_apple();
        return;
    }
    for (int i = 0; i < tailLength; i++) {
        if (fruitX == tailX[i] && fruitY == tailY[i])
            place_apple();
            break;
    }
}

void setup() {
    int user_input;
    cout << "1. classic \n" \
         << "2. classic_speedup \n" \
         << "3. nowalls \n" \
         << "4. nowalls_invincible \n" \
         << "~. exit \n" \
         << "Select a game mode: ";
    cin >> user_input;
    systemClearScreen();

    switch (user_input) {
    case 1:
        gamemode = CLASSIC;
        break;
    case 2:
        gamemode = CLASSIC_SPEEDUP;
        break;
    case 3:
        gamemode = NOWALLS;
        break;
    case 4:
        gamemode = NOWALLS_INVINCIBLE;
        break;
    default:
        forceQuit = true;
        break;
    }

    // Prebaking line of wall
    for (int i = 0; i < width; i++) { 
        wallLine += '#';
    }
    wallLine += '\n';

    // Prebaking empty line
    emptyLine = '#';
    for (int i = 2; i < width; i++) { 
        emptyLine += ' ';
    }
    emptyLine += "#\n";

    // Setting seed for random
    srand(time(0));

    // Initial head position
    headX = int(width/2);
    headY = int(height/2);

    // Placing an apple
    place_apple();
}

void draw() {
    // system("cls"); // system("clear") for linux
    cout <<"\x1b[H"; // faster way to clear
    
    // Top wall
    cout << wallLine;
    
    // Side walls and map
    bool isLineNotEmpty = false;
    for (int i = 0; i < height; i++) {
        if (fruitY != i && headY != i) {
            for (int j = 0; j < tailLength; j++) {
                if (tailY[j] == i) {
                    isLineNotEmpty = true;
                    break;
                }
            }
        } else {
            isLineNotEmpty = true;
        }
        if (isLineNotEmpty) {
            for (int j = 0; j < width; j++) {
                if (j == 0 || j == width-1)
                    cout << '#';
                else if (i == headY && j == headX)
                    cout << "\x1b[32mO\x1b[0m";
                else if (i == fruitY && j == fruitX)
                    cout << "\x1b[31ma\x1b[0m";
                else {
                    bool print = false;
                    for (int k = 0; k < tailLength; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            cout << "\x1b[32mo\x1b[0m";
                            print = true;
                            break;
                        }
                    }
                    if (!print)
                        cout << ' ';
                }
            }
            cout << '\n';
        } else {
            cout << emptyLine;
        }
    }

    // Bottom wall
    cout << wallLine;

    cout << "Score: " << score << endl;
    if (isDebugMode)
        cout << "DEBUG: \n" 
             << "fruit: (" << fruitX << ',' << fruitY << ") head: (" << headX << ',' << headY << ")\n" \
             << "sleepTime: " << sleepTime << " ms fps: " << 1000./sleepTime << "\n" \
             << "gridSize: (" << width << 'x' << height << ") gm: " << gamemode << endl;
}

void input() {
    if (_kbhit())
    {
        switch (_getch()) {
        case 75:
        case 'a':
            dir = LEFT;
            break;
        case 77:
        case 'd':
            dir = RIGHT;
            break;
        case 72:
        case 'w':
            dir = UP;
            break;
        case 80:
        case 's':
            dir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        case '`':
            isDebugMode = !isDebugMode;
            systemClearScreen();
            break;
        }
    }
}

void logic() {
    // Moving tail
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y; // Buffer
    tailX[0] = headX; // Move the first part on the previous head's place
    tailY[0] = headY; 

    // Start with 1,ּ as 0 tail part is already moved
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Moving head
    switch (dir) {
        case LEFT:
            headX--;
            break;
        case RIGHT:
            headX++;
            break;
        case UP:
            headY--;
            break;
        case DOWN:
            headY++;
            break;
    }

    // Check for collision with walls
    switch (gamemode) {
        case CLASSIC:
        case CLASSIC_SPEEDUP:
            if (headX <= 0 || headX >= width - 1 || headY < 0 || headY >= height)
                isGameOver = true;
            break;
        case NOWALLS:
        case NOWALLS_INVINCIBLE:
            if (headX >= width - 1)
                headX = 1;
            else if (headX <= 0)
                headX = width - 1;
            if (headY >= height)
                headY = 0;
            else if (headY < 0)
                headY = height - 1;
            break;
    }

    // Check for collision with tail
    if (gamemode != NOWALLS_INVINCIBLE) {
        for (int i = 0; i < tailLength; i++)
            if (tailX[i] == headX && tailY[i] == headY)
                isGameOver = true;
    }

    // Eating a fruit
    if (headX == fruitX && headY == fruitY) {
        score++;
        tailLength++;
        place_apple();
        // For speed-up gamemode - speeds up the game
        if (gamemode == CLASSIC_SPEEDUP && sleepTime > 30)
            sleepTime -= 2;
    }
}

void results() {
    cout << "\x1b[2J\x1b[H";
    cout << "\x1b[31m---Game Over!---\x1b[0m" << '\n';
    cout << "Final score: " << score << '\n';
}

int main() {
    setup();
    if (forceQuit)
        return 1;
    while (!isGameOver) {
        input();
        logic();
        draw();
        sleep_ms(sleepTime);
    }
    results();
    return 0;
}