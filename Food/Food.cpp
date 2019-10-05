#include "Food.h"
 
Food::Food()
{
 
}
 
Food::~Food()
{
 
}
 
void Food::init()
{
 
    generatePos();
 
}
 
void Food::draw(N5110 &lcd)
{
    // draws foot to LCD
    lcd.drawCircle(_x, _y, 1, FILL_TRANSPARENT);
}
 
void Food::generatePos()
{
 
    // create temporary x,y coordinates
    // randomize x coord for food
    srand(time(NULL));
    int temp_x = rand() % 80;
 
    if (temp_x == 0) {
 
        // prevent food from spawning outside boundary.
        temp_x = 1;
    }
 
    // finalize x coord
    _x = temp_x;
 
    // randomize y coord for food
    int temp_y = rand() % 41;
 
    // prevent food from spawning outside boundary.
    if (temp_y == 0) {
        temp_y = 1;
    }
 
    // finalize y coord
    _y = temp_y;
 
}
 
void Food::update()
{
 
    generatePos();
 
    // console message
    printf("New food position generated.\n");
}
 
Vector2D Food::get_pos()
{
    Vector2D p = {_x,_y};
    return p;
}
