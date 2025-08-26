// randomization based on remainders of division

#include <iostream>
#include <vector>


std::vector<float> random(int dividend, int divisor, int count) {

    int remainder = dividend % divisor;
    std::vector<float> rand = {};

    for (int i = 0; i < count; i++) {
        remainder = (10 * remainder) % divisor;
        rand.push_back(remainder);
    }

    // rand is in range [1, divisor - 1]
    // subtract 1 and divide by (divisor - 2) to bring it to [0, 1]
    // multiply by 16 to bring it to [0, 16]
    // 16 is the grid size

    for (int i = 0; i < count; i++) {
        rand[i] = (rand[i]-1)/(divisor - 2) * 16;
    }
    
    return rand;
}