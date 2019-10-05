#ifdef TEST_SCRIPT
#include "test_main.h"
#endif

/*
ELEC2645 Embedded Systems Project
School of Electronic & Electrical Engineering
University of Leeds
Name: Chun Nixon Pang
Username: el16cnp
Student ID Number: 201043292
Date: 13-4-2018
*/

#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "SnakeEngine.h"

#define SNAKE_WIDTH 1
#define START_LENGTH 1

/////////////// structs /////////////////
struct UserInput {
    Direction d;
    float mag;
};
/////////////// objects ///////////////
N5110 lcd(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11);
Gamepad pad;
SnakeEngine snake;

// prototype
void init();
void render();
void update_game(UserInput input);
void welcome();
void options();
void help1();
void help2();
void menuhelp();
void menuhelp25();
void menuhelp50();
void menuhelp75();
void menuhelp100();
void menuhelpstrings();

// main
int main()
{
    
    #ifdef TEST_SCRIPT
    int number_of_failures = test_all(pad, lcd);
    if(number_of_failures > 0) {
        return number_of_failures;
    }
    #endif
    
    // set lcd contrast
    printf("LCD contrast set to 0.4.\n");
    int fps = 32;  // frames per second
    printf("fps set to 32.\n");
    init();
    // initialise and then display welcome screen...
    printf("Game initialised.\n");

    menuhelp();

    welcome();  // waiting for the user to start

    printf("Showing menu.\n");

    printf("Start pressed. Rendering...\n");

    render();  // first draw the initial frame
    wait(1.0f/fps);  // and wait for one frame period


    // game loop - read input, update the game state and render the display
    while (1) {
        snake.read_input(pad);
        snake.update(pad, lcd);
        render();
        wait(1.0f/fps);
    }
}

// initialies all classes and libraries
void init()
{
    // need to initialise LCD and Gamepad
    lcd.init();
    pad.init();
    snake.init(SNAKE_WIDTH, START_LENGTH);
    printf("Init normal mode.\n");
    // initialise the game with correct ball and paddle sizes

}

// this function draws each frame on the LCD
void render()
{
    // clear screen, re-draw and refresh
    lcd.clear();
    snake.draw(lcd);
    lcd.refresh();
}

// simple splash screen displayed on start-up
void welcome()
{
    lcd.clear();

    // display lcd menu with normal mode preselected
    snake.displaynormal(lcd);

    // wait flashing LEDs until start button is pressed
    while ( pad.check_event(Gamepad::A_PRESSED) == false) {
        pad.leds_on();
        wait(0.1);
        pad.leds_off();
        wait(0.1);

        printf("mode %i\n", snake.mode);
        printf("displaymode %i\n", snake.displaymode);

        // verify if mode 0 is active
        snake.mode_0(pad);
        // verify if mode 1 is active
        snake.mode_1(pad);

        if (snake.displaymode == 1) {

            snake.displayborderless(lcd);
        }

        if (snake.displaymode == 0) {

            snake.displaynormal(lcd);
        }

    }

    // display first page help
    help1();
    printf("A pressed.\n");
    printf("Help page 1 displayed.\n");
    // wait flashing LEDs until R button is pressed

    snake.r_pressed(pad, lcd);

    // display second page help
    help2();
    printf("R pressed.\n");
    printf("Help page 2 displayed.\n");
    // wait flashing LEDs until start button is pressed

    snake.start_pressed(pad);

    printf("Start pressed.\n");



}

// first page help
void help1()
{
    lcd.clear();  // clear lcd
    lcd.printString("Controls:",0,1); // print lines
    lcd.printString("Joystick, or",0,2);
    lcd.printString("R: nxt pg",0,4);
    lcd.refresh(); // refresh lcd / show drawx
}

// second page help
void help2()
{
    lcd.clear();  // clear lcd
    lcd.printString("Y = Up",0,1); // print lines
    lcd.printString("A = Down",0,2);
    lcd.printString("X = Lf, B = Rt",0,3);
    lcd.printString("START to play",0,4);
    lcd.refresh(); // refresh lcd / show draw
}

void menuhelpstrings()
{
    lcd.printString("INSTRUCTIONS",0,1);
    lcd.printString("B TO SWAP MODE",0,2);
    lcd.printString("A TO ADVANCE",0,3);
}


void menuhelp25() {
    
    
    menuhelpstrings(); // print help strings
    lcd.drawRect(0,32,56,8,FILL_TRANSPARENT); // draw loading bar frame
    lcd.drawRect(0,32,14,8,FILL_BLACK); // draw loading bar
    lcd.printString("25%",60,4); // print percentage
    lcd.printString("Loading", 42,5);
    
}

void menuhelp50() {
    
    menuhelpstrings(); // print help strings
    lcd.drawRect(0,32,56,8,FILL_TRANSPARENT); // draw loading bar frame
    lcd.drawRect(0,32,28,8,FILL_BLACK); // draw loading bar
    lcd.printString("50%",60,4); // print percentage
    lcd.printString("Loading", 42,5);
    
}

void menuhelp75() {
    
    menuhelpstrings(); // print help strings
    lcd.drawRect(0,32,56,8,FILL_TRANSPARENT); // draw loading bar frame
    lcd.drawRect(0,32,42,8,FILL_BLACK); // draw loading bar
    lcd.printString("75%",60,4); // print percentage
    lcd.printString("Loading", 42,5);
    
}

void menuhelp100() {
    
    menuhelpstrings(); // print hjelp strings
    lcd.drawRect(0,32,56,8,FILL_TRANSPARENT); // draw loading bar frame 
    lcd.drawRect(0,32,56,8,FILL_BLACK); // draw loading bar
    lcd.printString("100%",60,4); // print percentage
    lcd.printString("Loaded", 48,5);
    
}

void menuhelp()
{
    lcd.clear(); // clear lcd
    menuhelp25(); // print 25%
    lcd.refresh(); // lcd refresh
    wait(0.75); // wait 1 second
    lcd.clear(); // clear lcd
    menuhelp50(); // print 50%
    lcd.refresh(); // lcd refresh
    wait(0.75); // wait 1 second
    lcd.clear(); // clear lcd
    menuhelp75(); // print 75%
    lcd.refresh(); // lcd refresh
    wait(0.75); // wait 1 second
    lcd.clear(); // clear lcd
    menuhelp100(); // print 100%
    lcd.refresh(); // lcd refresh
    wait(0.75); // wait 1 second

}
