/*!
* \class Food
* \brief Food properties
* \author Chun Nixon Pang
* \date Apr, 2018
*/

#ifndef FOOD_H
#define FOOD_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Snake.h"



class Food
{

public:

    /** Constructor */
    Food();

    /** Desctructor */
    ~Food();

    /** Initializes food properties
     * @param x-coord (int), y-coord (int), food diameter (int)
    */
    void init();

    /** Draw objects in LCD
     * @param LCD (lcd)
     */
    void draw(N5110 &lcd);

    /** Update user input to LCD
     * @return update
     */
    void update();

    /** Get Position (x,y) of food.
     * @return position of food
    */
    Vector2D get_pos();

private:

    void generatePos();
    
    int _x;
    int _y;
    

};

#endif