#include "convenience.hpp"
#include "apple_spawning.hpp"

#include <windows.h> // to enable virtual terminal processing
#include <conio.h> // for getch()
#include <vector>
#include <list>


// TODO: How to check if the current OS is Windows, if yes, only then we call the init() function


/*
Use these for virtual terminal sequences:
    - https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
    - https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
*/




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








std::list <Position> snake_position_array = {
    {10, 10}, {10, 11}, {10, 12}, {10, 13}
};


bool game_is_running = true;
int current_direction = RIGHT; // initial direction


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

    std::vector<float> apple_spawn_x = random(311, 113, 50); // array of random x coordinates
    std::vector<float> apple_spawn_y = random(457, 147, 50); // array of random y coordinates


    int i = 0; // current index in apple spawing array
    draw(apple_spawn_x[0], apple_spawn_y[0], RED); // draw first apple

    int score = 0;
    
    while(game_is_running) {
        draw(apple_spawn_x[i], apple_spawn_y[i], RED); // draw the current apple
        // the snake itself will erase the apple, no need to erase it manually
        display_score(score);

        // if snake has eaten apple
        if (snake_position_array.front() == Position(apple_spawn_x[i], apple_spawn_y[i])) {
            switch(current_direction) {
                case UP:
                snake_position_array.push_front(Position(snake_position_array.front().x, snake_position_array.front().y--));
                break;
                case DOWN:
                snake_position_array.push_front(Position(snake_position_array.front().x, snake_position_array.front().y++));
                break;
                case LEFT:
                snake_position_array.push_front(Position(snake_position_array.front().x--, snake_position_array.front().y));
                break;
                case RIGHT:
                snake_position_array.push_front(Position(snake_position_array.front().x++, snake_position_array.front().y++));
                break;
            }
            i++;
            score++;
        }


        switch(current_direction) {
            case UP:
                for (Position each : snake_position_array) erase(each.x, each.y); // erase previous snake

                // make "back" the "front" and remove back
                snake_position_array.push_front(Position(snake_position_array.front().x, snake_position_array.front().y - 1));
                snake_position_array.pop_back();

                for (Position each : snake_position_array) draw(each.x, each.y, GREEN); // draw snake
            break;

            case DOWN:
                for (Position each : snake_position_array) erase(each.x, each.y); // erase previous snake

                // make "back" the "front" and remove back
                snake_position_array.push_front(Position(snake_position_array.front().x, snake_position_array.front().y + 1));
                snake_position_array.pop_back();

                for (Position each : snake_position_array) draw(each.x, each.y, GREEN); // draw snake
            break;

            case LEFT:
                for (Position each : snake_position_array) erase(each.x, each.y); // erase previous snake

                // make "back" the "front" and remove back
                snake_position_array.push_front(Position(snake_position_array.front().x - 1, snake_position_array.front().y));
                snake_position_array.pop_back();

                for (Position each : snake_position_array) draw(each.x, each.y, GREEN); // draw snake
            break;

            case RIGHT:
                for (Position each : snake_position_array) erase(each.x, each.y); // erase previous snake

                // make "back" the "front" and remove back
                snake_position_array.push_front(Position(snake_position_array.front().x + 1, snake_position_array.front().y));
                snake_position_array.pop_back();

                for (Position each : snake_position_array) draw(each.x, each.y, GREEN); // draw snake
            break;

        } // switch statement

        delay(250);

    } // while loop

}

    
    

int main() {
    init();

    std::cout << "Press and key to start.";

    getch();
    clear_screen();
    
    std::thread input_thread (input_loop);
    std::thread game_thread (game_loop);

    input_thread.join();
    game_thread.join();

    std::cout << "finished";
    getch();
}