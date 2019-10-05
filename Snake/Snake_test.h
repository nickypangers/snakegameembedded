#ifndef SNAKE_TEST_H
#define SNAKE_TEST_H

/**
 * @brief Check that snake starts at the correct position and position after movement
 * @return true if test passes
*/

#include "Snake.h"

bool snake_test_movement(Gamepad &pad)
{
    printf("Snake Test Movement");
    Snake snake;
    
    snake.init(WIDTH/2,HEIGHT/2,1,1); // initial settings and set postion of snake to centre
    
    float _mag;
    Direction d = N;
    
    // start of movement
    // Up by 5
    for (int i = 0; i < 5; i++) {
        snake.checkdirection(d, _mag, pad);
    }
    
    // Right by 20
    d = E;
    
    for (int j = 0; j < 20; j++) {
        snake.checkdirection(d, _mag, pad);
    }
    
    Vector2D snakepos2 = snake.get_pos(); // get snake position (position after movement)
    
    int x2 = snakepos2.x;
    int y2 = snakepos2.y;
    
    printf("x2 = %i (62)| y2 = %i (19)\n", x2, y2);// print position after movement
    
    // if position after movement are equal to expected values
    // return true (pass)
    if (x2 == 62 && y2 == 19) {
        return true;
    } else { // if position after movement are not equal to expected values
             // return false (fail)
        return false;
    }
};

bool snake_test_spawn(Gamepad &pad)
{
    printf("Snake Test Spawn\n");
    Snake snake;
    
    snake.init(1,45,1,1); // initial settings and set postion of snake to 1,45
    Vector2D snakepos = snake.get_pos(); // get snake position (position before movement)
    int x1 = snakepos.x;
    int y1 = snakepos.y;
    
    printf("x1 = %i (1)| y1 = %i (45)\n",x1,y1); // print position before movement
    
    // if starting position is equal to expected values
    // return true (pass)
    if (x1 == 1 && y1 == 45) {
        return true;
    } else { // if starting position is not equal to expected values
             // return faalse (fail)
        return false;
    }
};


#endif