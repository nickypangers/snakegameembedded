/*!
* \class Snake
* \brief Snake head and body properties
* \author Chun Nixon Pang
* \date Apr, 2018
*/

#ifndef SNAKE_H
#define SNAKE_H

#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "Food.h"

class Snake
{
public:
    
    /** Constructor */
    Snake();
    
    /** Destructor */
    ~Snake();
    
    /** Initializes snake properties
     * @param starting x-coord (int), starting y-coord (int), starting height (int), starting width (int)
    */
    void init(int x, int y, int height, int width);
    
    
    /** Draw objects in LCD.
     * @param LCD (lcd)
    */
    void draw(N5110 &lcd);
    
    /** Update user input to LCD.
     * @param snake direction d, joystick magnitude mag (float), gamepad (pad)
    */
    void update(Direction d, float mag, Gamepad &pad);
    
    /** Add tail whenever the snake eats a food.
    */
    void addtail();
    
    /** Check snake direction and preventing snake from moving 180 degrees
     * @param direction d, joystick magnitude mag (float), gamepad (pad)
    */
    void checkdirection(Direction d, float mag, Gamepad &pad);
    
    /** Final direcion flag. Save user input unless user inputs new input
    */
    Direction finald;
    
    /** Get position (x,y) for Snake (head)
     * @return position of snake
    */
    Vector2D get_pos();

    /** Value of speed of which snake is moving.
    */
    int speed;
    
    /** Snake width
    */
    int swidth;
    
    /** X Snake Tail
    */
    int xtail[999];
    
    /** Y Snake Tail
    */
    int ytail[999];
    
    /** Tail Length
    */
    int nTail;
    
    /** Check if snake reaches border and reset coordinates accordingly
     * @return x and y coords of snake when reaching border
    */
    void check_borderless();

private:

    void finaldirection();
    void checkinput(Direction d);
    
    int _x;
    int _y;
    int _height;
    int _width;
    
    float _mag;
};
#endif