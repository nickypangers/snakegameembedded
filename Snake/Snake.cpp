#include "Snake.h"
 
Snake::Snake()
{
 
}
 
Snake::~Snake()
{
 
}
 
// initializes snake
void Snake::init(int x, int y, int height, int width)
{
    // set starting coorindates for snake (head)
    // x coord
    _x = x;
    // y coord
    _y = y;
    _height = height;
    _width = swidth;
    // start tail length to 0
    nTail = 0;
    // set first x-coord to snake x-coord
    xtail[0] = x;
    // set first y-coord to snake y-coord
    ytail[0] = y;
    // default starting snake movement direction is UP
    finald = N;
}
 
void Snake::draw(N5110 &lcd)
{
 
    // draws snake with the latest length
    lcd.drawRect(_x, _y, swidth, _height, FILL_BLACK);
    
    // set pixel for tail
    for (int k = 0; k < nTail; k++) {
 
        lcd.setPixel(xtail[k], ytail[k], true);
 
    }
}
 
void Snake::finaldirection()
{
 
    // snake running constantly at same direction
    // final direction set to UP, y constantly decreases
    if (finald == N) {
        _y = _y--;
    }
 
    // final direction set to DOWN, y constantly increases
    if (finald == S) {
        _y = _y++;
    }
 
    // final direction set to RIGHT, x constantly increases
    if (finald == E) {
        _x = _x++;
    }
 
    // final direction set to LEFT, x constantly decreases
    if (finald == W) {
        _x = _x--;
 
    }
 
}
 
void Snake::checkinput(Direction d)
{
    // change direction to UP
    if (d == N) {               // Y button pressed
        // prevent snake changing direction 180 deg
        // if snake is moving DOWN
        if (finald == S) {
            // direction remains DOWN
            d = S;
        }
        // confirm direction to final snake direction
        finald = d;
    }
 
    // change direction to RIGHT
    if (d == E) {              // B button pressed
        // prevent snake changing direction 180 deg
        // if snake is moving LEFT
        if (finald == W) {
            // direction remains LEFT
            d = W;
        }
        // confirm direction to final snake direction
        finald = d;
    }
 
    // change direction to DOWN
    if (d == S) {             // A button pressed
        // prevent snake changing direction 180 deg
        // if snake is moving UP
        if (finald == N) {
            // direction remains UP
            d = N;
        }
        // confirm direction to final snake direction
        finald = d;
    }
 
    // chagne direction to LEFT
    if (d == W) {             // X button pressed
        // prevent snake changing direction 180 deg
        // if snake is moving RIGHT
        if (finald == E) {
            // direction remains RIGHT
            d = E;
        }
        // confirm direction to final snake direction
        finald = d;
    }
 
}
 
// updates snake direction depending on user input
void Snake::checkdirection(Direction d, float mag, Gamepad &pad)
{
 
    // set direction flag to down if A pressed
    if ( pad.check_event(Gamepad::A_PRESSED) == true) {
        // user desires snake to move DOWN
        d = S;
    }
    // set direction flag to right if B pressed
    if ( pad.check_event(Gamepad::B_PRESSED) == true) {
        // user desires snake to move RIGHT
        d = E;
 
    }
    // set direction flag to left if X pressed
    if ( pad.check_event(Gamepad::X_PRESSED) == true) {
        // user desires snake to move LEFT
        d = W;
 
    }
    // set direction flag to up if Y pressed
    if ( pad.check_event(Gamepad::Y_PRESSED) == true) {
        // user desires snake to move UP
        d = N;
 
    }
 
    // check if input conflicts with snake current movement
    // if theres no conflict confirms final direction
    // if theres conflict remain previous direction
    checkinput(d);
 
    // changes snake direction to final direction
    finaldirection();
 
}
 
// check if snake reaches border
void Snake::check_borderless()
{
    // if snake reaches left border, reset snake to furthest right
    // (x coord)
    if (_x < 1) {
        _x = 83;
    }
    // if snake reaches right border, reset snake to furthest left
    // (x coord)
    if (_x > 83) {
        _x = 1;
    }
    // if snake reaches top border, reset snake to bottom
    // (y coord)
    if (_y < 1) {
        _y = 47;
    }
    // if snake reaches bottom border, reset snake to top
    // (y coord)
    if (_y > 47) {
        _y = 1;
    }
 
}
 
// Update snake
void Snake::update(Direction d, float mag, Gamepad &pad)
{
    // update tail
    addtail();
 
    // check user input on snake
    checkdirection(d, _mag, pad);
 
}
 
// add tail function
// reference: https://www.youtube.com/watch?v=PSoLD9mVXTA&t=379s
void Snake::addtail()
{
    // store previous coordinates
    int xtop1 = xtail[0];
    int ytop1 = ytail[0];
 
    // define new coordinates
    int xtop2, ytop2;
 
    // store current coordinates
    xtail[0] = _x;
    ytail[0] = _y;
 
    // loop through all tails and  updates new tail coordinates
    for (int a = 1; a < nTail; a++) {
        xtop2 = xtail[a];
        ytop2 = ytail[a];
 
        xtail[a] = xtop1;
        ytail[a] = ytop1;
 
        xtop1 = xtop2;
        ytop1 = ytop2;
 
    }
 
}
 
// get snake position
Vector2D Snake::get_pos()
{
    Vector2D p = {_x,_y};
    return p;
 
}
