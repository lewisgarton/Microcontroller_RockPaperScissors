/** @file   game.c
    @authors Janitha Gunathhilake, Lewis Garton
    @date   19 Oct 2017
    @brief  Main program to run the paper, scissors, rock game

    initializes required programs/modules and exacutes the  paper,
    * scissors, rock game.
*/


#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "button.h"
#include "stdbool.h"
#include "game_types.h"
#include "ir_uart.h"
#include "game_helper.c"
#include "uint8toa.h"
#include "button.c"
#include "communication.c"
#include "logic.c"
#include "game_init.c"


// Timing Settings

int main (void)
{
    // Tick counter
    uint16_t tick = INIT_ZERO;
    state_t game_state;
    
    // Scrolling screen text
    char* scroll_screen = "SELECT PLAYER PRESS DOWN BUTTON";
    
    // Initialising all systems
    system_init ();
    init_tinygl();
    navswitch_init();
    ir_uart_init ();

    // Displaying the scroll screen
    tinygl_text(scroll_screen);

    // Initializing for game state
    init_player(&game_state);
    
    
	// Starting the game
	while (1) {
		
		navswitch_update();
		pacer_wait ();
		tinygl_update ();
		
		// Check to see if the player has started the game
		if (!game_state.game_started){
			game_state.game_started = game_status();
			continue;
		}
		
		// Check if the player is selected
		if(game_state.player_selected == FALSE) {				
			select_player(&game_state);
			display_character (game_state.player);				
			continue;                
		} 
		
		// Check if opponent has selected     
		if(game_state.selection_final == false) {
			choose_selection(&game_state);
			continue;
		} 
				
		// Player one, gets opponents choice, computes and displays it.
		if(game_state.player == PLAYER_ONE) {
			get_opponent(&game_state);
			
			// If the player has chosen
			if(game_state.opponent_selection != INIT_ZERO) {
				// Compute result
				if(!game_state.result_set) {
					get_result(&game_state);
					game_state.result_set = TRUE;
				} 
				else {
					// Display the result
					display_result(&game_state);
				}
			}
		}                    
				

		// Player two recieves and displays result
		if(game_state.player == PLAYER_TWO) {
			// Check if result is received
			if(!game_state.result_set) {
				// get the result
				ir_rcv_result(&game_state);
			} 
			else {
				// Invert and display the results
				invert_result(&game_state);
				display_result(&game_state);
			}
		}


		// Reset game on navswitch push
		if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
			reset_game(&game_state);
			tinygl_clear();
		}

		// Sending IR at diffrent rates
		tick++;
		if (tick > PACER_RATE / MESSAGE_RATE) {
			tick = 0;

			// Check if result is set, send the result to player two
			if (game_state.player == '1' && game_state.result_set) {
				if (game_state.sent == false) {
					game_state.sent = send_char (game_state.round_result);
				}
			}
			
			// Send choice to player 1
			if (game_state.player == '2') {
				if (game_state.sent == false) {
					game_state.sent = send_char (game_state.player_selection);
				}
			}
		}
	}
}

