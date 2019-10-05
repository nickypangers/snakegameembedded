#ifndef TEST_MAIN_H
#define TEST_MAIN_H

/**
 * @brief Run through all tests and return results
 * @return final no. of test(s) failed
*/

#include "Snake_test.h"

int test_all(Gamepad &pad, N5110 &lcd)
{
    // set no. of failed to 0
    int _failed = 0;
    
    // if snake spawn test failed
    if (snake_test_spawn(pad) == false) {
        // no. of failed + 1
        _failed++;
        printf("TEST: snake_test_spawn FAIL\n"); // print failed
        
    } else { // if snake test spawn pass, no. of failed unchanged
        printf("TEST: snake_test_spawn PASS\n"); // print passed
    }
    
    // if snake movement test failed
    if (snake_test_movement(pad) == false) {
        _failed++; // no. of failed + 1
        printf("TEST: snake_test_movement FAIL\n"); // print failed
    } else { // if snake movement test pass, no. of failed unchanged
        printf("TEST: snake_test_movement PASS\n"); // print passed
    }
    
    // return final no. of failed
    return _failed;
};

#endif