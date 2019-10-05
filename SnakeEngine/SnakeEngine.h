/*!
* \class SnakeEngine
* \brief Game engine for Snake
* \author Chun Nixon Pang
* \date Apr, 2018
*/

#ifndef SNAKEENGINE_H
#define SNAKEENGINE_H

#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "Snake.h"
#include "Food.h"

class SnakeEngine
{

public:

    /** Constructor */
    SnakeEngine();

    /** Destructor */
    ~SnakeEngine();

    /** Initializing game parameters
     * @param width of snake (int), length of snake (int), size of food (int)
    */
    void init(int snake_width, int start_length);

    /** Read user input
     * @param gamepad (pad)
    */
    void read_input(Gamepad &pad);

    /** Update user input to LCD
     * @param gamepad (pad), LCD (lcd)
    */
    void update(Gamepad &pad, N5110 &lcd);

    /** Draw objects to LCD
     * @param LCD (lcd)
    */
    void draw(N5110 &lcd);

    /** Kill screen when snake dies
     * @param gamepad (pad), LCD (lcd)
    */
    void killscreen(Gamepad &pad, N5110 &lcd);

    /** Restart Game Loop
     * @param gamepad (pad), LCD (lcd)
    */
    void restartgame(Gamepad &pad, N5110 &lcd);

    /** value of user score
     * @return value of user score (int)
     */
    int score;

    /** Value of highscore
     * @return highscore (int)
    */
    int highscore;

    /** Value of mode (0/1)
     * @return mode (int)
    */
    int mode;

    /** Value of display mode (0/1)
     * @return display mode (int)
    */
    int displaymode;

    /** Display predefined strings for normal mode on LCD
     * @param LCD (lcd)
    */
    void displaynormal(N5110 &lcd);

    /** Display predefined strings for borderless mode on LCD
     * @param LCD (lcd)
    */
    void displayborderless(N5110 &lcd);

    /** Check if R button pressed by user
     * @param gamepad (pad), LCD (lcd)
    */
    void r_pressed(Gamepad &pad, N5110 &lcd);

    /** Check if START button pressed by user
     * @param gamepad (pad)
    */
    void start_pressed(Gamepad &pad);

    /** Check which mode is selected by user
     * @param gamepad (pad), LCD (lcd)
    */
    void mode_check(Gamepad &pad, N5110 &lcd);

    /** Mode 0 (Normal Mode)
     * @param gamepad (pad)
    */
    void mode_0(Gamepad &pad);

    /** Mode 1 (Borderless Mode)
     * @param gamepad (pad)
    */
    void mode_1(Gamepad &pad);
    
    /** Death Count
     * @return number of death
    */    
    int death_count;
    
    /** Check whether snake head hits the wall
     * @param gamepad (pad), LCD (lcd)
    */
    void check_wall_collision(Gamepad &pad, N5110 &lcd);

private:
    
    void showkillscreen(Gamepad &pad, N5110 &lcd);
    void check_food_collision(Gamepad &pad);
    void playtone(Gamepad &pad);
    void restartwelcome(Gamepad &pad, N5110 &lcd);
    void restarthelp1(Gamepad &pad, N5110 &lcd);
    void restarthelp2(Gamepad &pad, N5110 &lcd);
    void check_tail_collision(Gamepad &pad, N5110 &lcd);
    void restartwelcome_display(N5110 &lcd);
    void back_pressed(Gamepad &pad);
    void highscorecheck(N5110 &lcd);

    Snake _snake;

    int _snake_width;
    int _start_length;

    int _snake_x;
    int _snake_y;

    Food _food;

    int _food_x;
    int _food_y;
    int _food_size;

    Direction _d;
    float _mag;

    int printhighscore; // print highscore
    int printscore; // print current score
    int printprevhigh; // print previous high score

};

#endif


