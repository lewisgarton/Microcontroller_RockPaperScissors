/** @file   logic.c
    @authors Janitha Gunathhilake, Lewis Garton
    @date   19 Oct 2017
    @brief  Provides required logic to run the game.

    initializes required programs/modules and exacutes the  paper,
    * scissors, rock game.
*/


#include "navswitch.h"
#include "tinygl.h"
#include "game_types.h"


/*Function to check the state of the game*/
int game_status (void)
{
	int flag = 0;
    navswitch_update();
    // Game is started by pulling down the navigation button
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        flag = 1;
        // Clearing the display
        tinygl_clear();
    }
    return flag;
}


/* Displays character on the led matrix */
void display_character (char character)
{
    // buffer to hold the ouput text
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    // Sending the chracters to the display
    tinygl_text (buffer);
}


/* Increments players choice in the games state, choice of PSR */
void choose_selection (state_t* game_state)
{	
	// Scrolling right in the list
	if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
		if (game_state->player_selection == PAPER) {
			game_state->player_selection = SCISSORS;
		}
		else if (game_state->player_selection == SCISSORS) {
			game_state->player_selection = ROCK;
		}
	}
	
	if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
		if (game_state->player_selection == ROCK) {
			game_state->player_selection = SCISSORS;
		}
		else if (game_state->player_selection == SCISSORS) {
			game_state->player_selection = PAPER;
		}
	}
	display_character (game_state->player_selection);
	if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
		game_state->selection_final = true;
		tinygl_clear();
	}
}


/* Increments player number choice in the games state, choice of player1, player2
 * If nav button is pressed, indicated selection chosen */
void select_player (state_t* game_state)
{
    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        game_state->player = PLAYER_ONE;
    }

    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        game_state->player = PLAYER_TWO;
    }
    
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
		game_state->player_selected = true;
		tinygl_clear();
	}
}


/* Computes the result of the game and stores in game state result */
void get_result (state_t* state)
{
	char result;
	
	if (state->player_selection == state->opponent_selection) {
		result = DRAW;
	} 
	else if (state->player_selection == ROCK && state->opponent_selection == SCISSORS) {
		result = WIN;
	} 
	else if (state->player_selection == PAPER && state->opponent_selection == ROCK) {
		result = WIN;
	} 
	else if (state->player_selection == SCISSORS && state->opponent_selection == PAPER) {
		result = WIN;
	} 
	else {
		result = LOSE;
	}
	
	state->round_result = result;
}


/* Inverts the result of a round */ 
void invert_result (state_t* game_state)
{
    if (game_state->round_result == WIN) {
        game_state->round_result = LOSE;
    } 
    else if (game_state->round_result == LOSE){
        game_state->round_result = WIN;
    }
}


// Function to display the results
void display_result(state_t* game_state)
{
    if(game_state->game_over == false && game_state->sent) {

        if(game_state->round_result == WIN) {
            tinygl_text("WINNER");
        } else if (game_state->round_result == LOSE) {
            tinygl_text("LOSER");
        } else {
            tinygl_text("DRAW");
        }
        game_state->game_over = true;
    }
}
