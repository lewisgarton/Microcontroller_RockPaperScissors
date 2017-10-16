#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "button.h"
#include "stdbool.h"

#define PACER_RATE 500
#define MESSAGE_RATE 20



void print_matrix (char* message)
{
    // Initialising the led matrix scroling
    
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    
    tinygl_text(message);
}



/*
int game_status (int start)
{
    while (start == 0) {
        pacer_wait ();
        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            start = 1;
        }
    }
    return start;
}
*/

int main (void)
{
    system_init ();
    tinygl_init (PACER_RATE);
    pacer_init (PACER_RATE);
    
    // Initialising the nav switch

    navswitch_init ();


    char* scroll_screen = "PRESS NAV BUTTON";

/*
    // checking the game status
    int start = 0;
    start = game_status(start);
*/

    print_matrix(scroll_screen);

    while (1) {
        
        
        pacer_wait();
        tinygl_update();
        navswitch_update ();
       
        


    }
}
