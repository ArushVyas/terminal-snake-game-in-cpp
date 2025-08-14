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


// refer: https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#text-formatting for colors
enum color {
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
};


void draw(uint x, uint y, int color) {
    std::cout << "\x1b[?25l"; // hide cursor

    std::cout << "\x1b[" << y << ";" << x * 2 << "H"; // set the cursor position

    std::cout << "\x1b[" << color << "m"; // set color
    std::wcout << L'\xDB' << L'\xDB'; // \xDB is a full block character
    std::cout << "\x1b[0m"; // reset color
}


void erase(uint x, uint y) {
    std::cout << "\x1b[" << y << ";" << x * 2 << "H"; // set the cursor position
    //                                      ^ because: line_height = 2 * line_width

    // erase 2 characters at the cursor position and replace them with space
    std::cout << "\x1b[1X";
    std::cout << "\x1b[1C"; // move cursor to the right by 1
    std::cout << "\x1b[1X";

}


inline void delay(uint milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


void clear_screen() {
    std::cout << "\x1b[2J\x1b[H";
}
