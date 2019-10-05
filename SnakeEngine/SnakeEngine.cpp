#include "SnakeEngine.h"

SnakeEngine::SnakeEngine()
{

}

SnakeEngine::~SnakeEngine()
{

}

// initialize
void SnakeEngine::init(int snake_width, int start_length)
{   

    // int game param
    // snake width
    _snake_width = snake_width;
    // snake length
    _start_length = start_length;

    // initialize snake and food
    _snake.init(WIDTH/2, HEIGHT/2, _snake_width, _start_length);
    _food.init();
    // reset score to 0.
    score = 0;;
    // set snake speed to 1 pixel per move
    _snake.speed = 1;
    _snake.swidth = 2;
    
    death_count = 0;


}

// read user input
void SnakeEngine::read_input(Gamepad &pad)
{
    // get gamepad direction
    _d = pad.get_direction();
    // get gamepad magnitude
    _mag = pad.get_mag();
}

// Drawing snake engine
void SnakeEngine::draw(N5110 &lcd)
{   
    if (mode == 0) {
        // draw game boundary
        lcd.drawRect(0,0,WIDTH,HEIGHT,FILL_TRANSPARENT);
    } else {
        lcd.drawRect(0,0,WIDTH,HEIGHT,FILL_WHITE);
    }
    // draw snake
    _snake.draw(lcd);
    // draw food
    _food.draw(lcd);
}

void SnakeEngine::update(Gamepad &pad, N5110 &lcd)
{
    // check if snake eaten food
    check_food_collision(pad);

    // update snake information
    _snake.update(_d, _mag, pad);

    // check game mode
    if (mode == 0) { // normal mode selected
        // border collision on
        check_wall_collision(pad, lcd);
        
    } else { // borderless mode selected
        // border collision off, resets snake coords when reaching border
        _snake.check_borderless();
    }

    // tail collision on, kills snake if head collides with tail
    check_tail_collision(pad, lcd);
    
    showkillscreen(pad, lcd);

}

// play tone whenever food eaten
void SnakeEngine::playtone(Gamepad &pad)
{
    // set frequency and duration of tone
    pad.tone(1000,0.2);

}

// check oif food is eaten or not
void SnakeEngine::check_food_collision(Gamepad &pad)
{
    // get snake position
    Vector2D snakepos = _snake.get_pos();
    // snake x coord
    int sx = snakepos.x;
    // snake y coord
    int sy = snakepos.y;
    printf("snake x = %i, y = %i\n", sx, sy);

    // get food position
    Vector2D foodpos = _food.get_pos();
    // food x coord
    int fx = foodpos.x;
    // food y coord
    int fy = foodpos.y;
    printf("food x = %i, y = %i\n", fx, fy);

    // if snake coord = food coord
    if (sx == fx && sy == fy) {
        // food update position
        _food.update();
        // score increases by 1
        score++;
        printf("Score + 1. Score now: %i\n", score);
        // play tone
        playtone(pad);
        // tail increases by 4
        _snake.nTail = _snake.nTail + 4;
        printf("New length: %i\n", _snake.nTail);

    }

}

void SnakeEngine::showkillscreen(Gamepad &pad, N5110 &lcd)
{
    if (death_count == 1) {
        printf("Kill screen displayed.\n");
        killscreen(pad, lcd);
    }
    
}

// wall collision
void SnakeEngine::check_wall_collision(Gamepad &pad, N5110 &lcd)
{
    // get snake position
    Vector2D checkwallpos = _snake.get_pos();
    // snake x coord
    int dx = checkwallpos.x;
    // snake y coord
    int dy = checkwallpos.y;

    // game over if snake x coord is smaller than x = 1
    if (dx < 1) {
        lcd.clear(); // clear lcd
        printf("Hit border.\n");
        death_count = 1;

    }
    // game over if snake x coord is greater than x = 83
    if (dx > 83) {
        lcd.clear(); // clear lcd
        printf("Hit border.\n");
        death_count = 1;

    }
    // game over if snake y coord is smaller than y = 1
    if (dy < 1) {
        lcd.clear(); // clear lcd
        printf("Hit border.\n");
        death_count = 1;

    }
    // game over if snake y coord is greater than y = 47
    if (dy > 47) {
        lcd.clear(); // clear lcd
        printf("Hit border.\n");
        death_count = 1;

    }


}

// tail collision
void SnakeEngine::check_tail_collision(Gamepad&pad, N5110 &lcd)
{
    // get snake position
    Vector2D snakepos = _snake.get_pos();
    // snake x coord
    int x = snakepos.x;
    // snake y coord
    int y = snakepos.y;

    // loop all snake tail coordinates
    for (int i = 0; i < _snake.nTail; i++) {
        // if snake coord matches any tail coord, game over.
        if (_snake.xtail[i] == x &&  _snake.ytail[i] == y) {
            lcd.clear(); // clear lcd
            printf("Snake x = %i, y = %i\n", x,y);
            printf("Tail x [%i] = %i , Tail y[%i] = %i\n", i, _snake.xtail[i], i, _snake.ytail[i]);
            printf("Snake tail blocked snake head. End game.\n");

            killscreen(pad, lcd); // game over screen

        }

    }

}

void SnakeEngine::highscorecheck(N5110 &lcd)
{

    // add score to highscore when highscore = 0
    // replace highscore with score when highscore is broken
    if (score > highscore) {
        // store previous highscore
        printprevhigh = highscore;
        // store new highscore
        highscore = score;
        // print highscore
        printhighscore = highscore;
        // print score
        printscore = score;
        // display current score and highscore
        lcd.printString("Score/HS(NEW):", 0, 2);
        printf("HS(%i), score(%i), new highscore(%i).\n", printprevhigh, printscore, printhighscore);
    }
    // highscore remains when score is lower than highscore
    else {
        highscore = highscore; // highscore doesnt change
        score = score; // score
        printhighscore = highscore; // print highscore
        printscore = score; // print highscore
        // display current score and highscore
        lcd.printString("Score/HS:", 0, 2);
        printf("HS(%i), score(%i),Highscore(%i) remains.\n", printhighscore, printscore, printhighscore);
    }

}


// game over screen
void SnakeEngine::killscreen(Gamepad &pad, N5110 &lcd)
{

    highscorecheck(lcd);

    // create character
    char buffer1[14];
    // print character
    sprintf(buffer1, "%i / %i", score, highscore);
    if (mode == 0) {  // normal mode selected
        // display mormal mode string on lcd
        lcd.printString("End. Normal", 0, 1);
    } else {  // borderless mode selected
        // display borderless mode string on lcd
        lcd.printString("End.Borderless", 0, 1);
    }
    // print strings on lcd
    lcd.printString(buffer1,0,3);
    lcd.printString("BACK to menu.",0,4);
    lcd.refresh();  // refresh lcd

    back_pressed(pad); // check if BACK button is pressed

    restartgame(pad, lcd); // restart game
    printf("Restarting game.\n");

}

// check if back button is pressed by user
void SnakeEngine::back_pressed(Gamepad &pad)
{
    // continue to flash LCD in a loop unless user presses BACK button
    while ( pad.check_event(Gamepad::BACK_PRESSED) == false) {
        // LEDs on
        pad.leds_on();
        wait(0.1); // wait for 0.1 second
        // LECs off
        pad.leds_off();
        wait(0.1); // wait for 0.1 second
    }

}

// restart the game after game over
void SnakeEngine::restartgame(Gamepad &pad, N5110 &lcd)
{

    lcd.clear();
    printf("Clearing LCD screen.\n");
    // show restart welcome screen on lCD
    restartwelcome(pad, lcd);
    // initialize game engine
    init(_snake_width, _start_length);
    printf("Preparing game...\n");
    lcd.refresh();
    printf("Game displayed.\n");

}

// restart welcome screen
void SnakeEngine::restartwelcome_display(N5110 &lcd)
{
    lcd.printString("     Snake!    ",0,1);
    lcd.refresh();
    printf("Displaying welcome screen.\n");
}

// preset strings to display on LCD when Normal mode is selected
void SnakeEngine::displaynormal(N5110 &lcd)
{

    lcd.clear();
    lcd.printString("     Snake!    ",0,1);
    lcd.printString("    Normal  < ",0,2);
    lcd.printString("  Borderless ",0,3);
    lcd.refresh();

}

// preset strings to display on LCD when Borderless mode is selected
void SnakeEngine::displayborderless(N5110 &lcd)
{

    lcd.clear();
    lcd.printString("     Snake!    ",0,1);
    lcd.printString("     Normal  ",0,2);
    lcd.printString(" Borderless < ",0,3);
    lcd.refresh();

}


void SnakeEngine::restartwelcome(Gamepad &pad, N5110 &lcd)
{

    lcd.clear();
    // restart welcome screen
    restartwelcome_display(lcd);
    // wait flashing LEDs until start button is pressed
    while ( pad.check_event(Gamepad::A_PRESSED) == false) {
        pad.leds_on();
        wait(0.1);
        pad.leds_off();
        wait(0.1);
        printf("mode %i\n", mode);
        printf("displaymode %i\n", displaymode);
        // check which mode is active
        mode_check(pad, lcd);
    }

    printf("Start button pressed.\n");

    // display first page help
    restarthelp1(pad, lcd);
    // wait flashing LEDs until R button is pressed
    r_pressed(pad, lcd);

    printf("R button pressed.\n");

    // display second page help
    restarthelp2(pad, lcd);
    // wait flashing LEDs until start button is pressed
    start_pressed(pad);
    printf("Start button pressed.\n");

}

// check if normal mode is chosen
void SnakeEngine::mode_0(Gamepad &pad)
{
    // check if current mode is selected to normal
    if (mode == 0) {
        if ( pad.check_event(Gamepad::B_PRESSED) == true) {
            // set mode to borderless
            mode = 1;
            // set display mode to borderless
            displaymode = 1;
            printf("Mode changed to borderless.\n");
        } else {
            // mode remains normal
            mode = 0;
            // display mode remains normal
            displaymode = 0;
        }
    }

}

// check if borderless mode is chosen
void SnakeEngine::mode_1(Gamepad &pad)
{
    // check if current mode is selected to borderless
    if (mode == 1) {
        if ( pad.check_event(Gamepad::B_PRESSED) == true) {
            // set mode to normal
            mode = 0;
            // set display mode to normal
            displaymode = 0;
            printf("Mode changed to normal.\n");
        } else {
            // mode remains borderless
            mode = 1;
            // display mode remains borderless
            displaymode = 1;
        }
    }
}

// check which mode user chosen
void SnakeEngine::mode_check(Gamepad &pad, N5110 &lcd)
{

    mode_0(pad);

    mode_1(pad);

    if (displaymode == 1) {
        lcd.clear();
        // display preset strings for borderless mode to LCD
        displayborderless(lcd);
    }

    if (displaymode == 0) {
        lcd.clear();
        // display preset strings for normal mode to LCD
        displaynormal(lcd);
    }

}

// check if start button is pressed by user
void SnakeEngine::start_pressed(Gamepad &pad)
{

    // flashing LEDs until start button is pressed
    while ( pad.check_event(Gamepad::START_PRESSED) == false) {
        pad.leds_on();
        wait(0.1);
        pad.leds_off();
        wait(0.1);

    }

}

// check if r button is pressed by user
void SnakeEngine::r_pressed(Gamepad &pad, N5110 &lcd)
{
    // flashing LEDs until r button is pressed
    while ( pad.check_event(Gamepad::R_PRESSED) == false) {
        pad.leds_on();
        wait(0.1);
        pad.leds_off();
        wait(0.1);

    }

}

// preset help strings to show on LCD (first page)
void SnakeEngine::restarthelp1(Gamepad &pad, N5110 &lcd)
{

    lcd.clear();
    lcd.printString("Controls:",0,1);
    lcd.printString("Joystick, or",0,2);
    lcd.printString("R: nxt pg",0,4);
    lcd.refresh();

}

// preset help strings to show on LCD (second page)
void SnakeEngine::restarthelp2(Gamepad &pad, N5110 &lcd)
{

    lcd.clear();
    lcd.printString("Y = Up",0,1);
    lcd.printString("A = Down",0,2);
    lcd.printString("X = Lf, B = Rt",0,3);
    lcd.printString("START to play",0,4);
    lcd.refresh();

}


