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
    bool chosen = false;
    choice_t player = 0;
    //choice_t opponent = NONE;

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

            if (chosen == false) { // Untill player has chosen
            /* TODO: Call the navswitch update function.  */
                navswitch_update ();

                if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                    if (player < 2) {
                    player += 1;
                    }
                }
                /* TODO: Increment character if NORTH is pressed.  */

                if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                    if (player > 0) {
                        player -= 1;
                    }
                }
                /* TODO: Decrement character if SOUTH is pressed.  */

                display_character (character[player]);

               if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                    chosen = true;

                }
            }

        }

    }

}


















