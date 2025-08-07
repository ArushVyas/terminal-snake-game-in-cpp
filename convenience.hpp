#include <iostream>
#include <thread>




typedef unsigned int uint;


class Position {
    public:
    uint x, y;

    Position(uint x_coord, uint y_coord) {
        x = x_coord;
        y = y_coord;
    }
};


enum direction {
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


void clear_screen() {
    std::cout << "\x1b[2J\x1b[H";
}
