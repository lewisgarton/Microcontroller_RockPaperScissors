#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "button.h"
#include "stdbool.h"
#include "game_types.h"


#define PACER_RATE 500
#define MESSAGE_RATE 20


/* Function to display the input character in the matrix */
void display_character (char character)
{
    // buffer to hold the ouput text
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    // Sending the chracters to the display
    tinygl_text (buffer);
}

/* Function to display a scrolling text in the matrix */
void display_string (char* message)
{
    // Seting up the display settings
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_speed_set (MESSAGE_RATE);
    // Sending the messasge to the display
    tinygl_text (message);

}

/*Initialising the matrix display*/
void my_matrix_init (void)
{
    // Seting up the tinygl library
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    // Initialising the pacer
    pacer_init (PACER_RATE);
}


/*Function to check the state of the game*/
bool game_status (int start)
{
    navswitch_update();
    // Game is started by pulling down the navigation button
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        start = 1;
        // Clearing the display
        tinygl_clear();
    }

    return start;
}


int main (void)
{
    // Arrays for selecting the game variables
    char character[3] = {'P','S','R'};
    // Scrolling screen text
    char* scroll_screen = "PRESS DOWN BUTTON";

    
    bool chosen = false;
    choice_t player = 0;


    // Initialising systems
    system_init ();
    // Initialising display driver
    my_matrix_init();
    // Initialising inputs
    navswitch_init();

    // Displaying the scroll screen
    display_string(scroll_screen);


    while(1) {

        // Checing for the state of the game
        bool start = 0;
        start = game_status(start);

        // Scrolling startup screen before game starts
        while (start == 0) {
            navswitch_update();
            pacer_wait ();
            tinygl_update ();
            break;
        }

        // Staring the game
        while (start == 1) {

            pacer_wait ();
            tinygl_update ();

            // Untill player has chosen
            if (chosen == false) {
                
                // Checking the navswitch
                navswitch_update ();
                
                // Scrolling right in the list 
                if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                    if (player < 2) {
                        player += 1;
                    }
                }
                
                // Scrolling left in the list
                if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                    if (player > 0) {
                        player -= 1;
                    }
                }
                
                // Showing the current letter in the display
                display_character (character[player]);
                

            }

        }

    }

}


















