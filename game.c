#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 20



void matrix_init (void)
{
    // Initialising the led matrix scroling
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    pacer_init (PACER_RATE);
}


void print_matrix (string)
{
    tinygl_text(string);
}



int main (void)
{
    system_init ();
    matrix_init ();
    
    
    // Initialising the nav switch
    navswitch_init();

    print_matrix("HELLO");
    
    while (1)
    {
        pacer_wait();
        tinygl_update ();
        navswitch_update ();
        
        

    }
}
