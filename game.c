#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "button.h"
#include "stdbool.h"


#define PACER_RATE 500
#define MESSAGE_RATE 20

/////////////////////////// to be moved to a module (I DONT KNOW WHAT YET)
// enum for player choice
typedef enum {
    ROCK,
    PAPER,
    SCISSORS,
    NONE = 0
} choice_t;

// enum for result
typedef enum {
    WIN,
    LOSE,
    DRAW,
    UNKNOWN = 0
} result_t;

result_t get_result(choice_t player, choice_t opponent) {
    result_t result =  UNKNOWN;
    if (player == opponent) {
        result = DRAW;
    } else if (player == ROCK && opponent == SCISSORS) {
        result = WIN;
    } else if (player == PAPER && opponent == ROCK){
        result = WIN;
    } else if (player == SCISSORS && opponent == PAPER) {
        result = WIN;
    } else {
        result = LOSE;
    }
    return result;
}
/////////////////////////////










void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

void display_string (char* message)
{
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_speed_set (MESSAGE_RATE);

    tinygl_text (message);

}

void my_matrix_init (void)
{
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);

    pacer_init (PACER_RATE);
}

bool game_status (int start)
{
    navswitch_update();
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        start = 1;
        tinygl_clear();
    }

    return start;
}


int main (void)
{
    char character[3] = {'P','S','R'};
    char* scroll_screen = "PRESS NAV BUTTON";
    int i = 0;
    int chosen;

    system_init ();

    /* Initialise display driver.  */
    my_matrix_init();

    navswitch_init();
    /* TODO: Initialise navigation switch driver.  */

    display_string(scroll_screen);

    while(1) {


        bool start = 0;
        start = game_status(start);

        while (start == 0) {
            navswitch_update();
            pacer_wait ();
            tinygl_update ();
            break;
        }


        while (start == 1) {

            pacer_wait ();
            tinygl_update ();
            navswitch_update ();
            /* TODO: Call the navswitch update function.  */

            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                i += 1;
            }
            /* TODO: Increment character if NORTH is pressed.  */

            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                i -= 1;
            }
            /* TODO: Decrement character if SOUTH is pressed.  */

            display_character (character[i]);

           if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                chosen = i;

            }

        }

    }

}


















