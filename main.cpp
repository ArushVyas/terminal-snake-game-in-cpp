#include <iostream>
#include <windows.h>
#include <conio.h> // for getch()
#include <thread>


// TODO: Start figuring out snake movement, probably has to do something with arrays


/*
Use these for virtual terminal sequences:
    - https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
    - https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
*/


// Convenience ------------------------
typedef unsigned int uint;


enum direction { //TODO: implement this
    LEFT, RIGHT, UP, DOWN
};


void draw(std::string draw_this_string, uint x, uint y) {
    std::cout << "\x1b[" << y << ";" << x << "H"; // set the cursor position

    std::cout << draw_this_string;
}


void erase(uint x, uint y) {
    std::cout << "\x1b[" << y << ";" << x << "H"; // set the cursor position

    std::cout << "\x1b[1X"; // erase 1 character at the cursor position and replace it with space
}


inline void delay(uint milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Convenience ends ----------------------- inconvenience starts


// Required to enable virtual terminal processing on windows platforms
void init() {

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD dwModeIn, dwModeOut;

    // Get current console modes
    GetConsoleMode(hIn, &dwModeIn);
    GetConsoleMode(hOut, &dwModeOut);

    // Enable virtual terminal flags
    dwModeIn |= ENABLE_VIRTUAL_TERMINAL_INPUT;
    dwModeOut |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    SetConsoleMode(hIn, dwModeIn);
    SetConsoleMode(hOut, dwModeOut);

}








bool game_is_running = true;
int current_direction = UP; // initial direction


void input_loop() {

    while (game_is_running) {
        switch(getch()) {
            case 'w':
            current_direction = UP;
            break;
            
            case 'a':
            current_direction = LEFT;
            break;

            case 's':
            current_direction = DOWN;
            break;

            case 'd':
            current_direction = RIGHT;
            break;
        }
    }

}


void game_loop() {
    int x = 10, y = 10;
    draw("O", x, y);
    
    while(game_is_running) {
        switch(current_direction) {
            case UP:
            erase(x, y);
            y--;
            draw("O", x, y);
            break;
            
            case DOWN:
            erase(x, y);
            y++;
            draw("O", x, y);
            break;

            case LEFT:
            erase(x, y);
            x--;
            draw("O", x, y);
            break;

            case RIGHT:
            erase(x, y);
            x++;
            draw("O", x, y);
            break;

        }
        delay(250);
    }
}




int main() {
    init();

    std::thread input_thread (input_loop);
    std::thread game_thread (game_loop);

    input_thread.join();
    game_thread.join();

    std::cout << "finished";
    getch();
}