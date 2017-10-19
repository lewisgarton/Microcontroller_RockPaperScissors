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

// Timing Settings
#define PACER_RATE 300
#define MESSAGE_RATE 10
#define TEXT_SPEED 30


// Game State defaults
#define INIT_ZERO 0
#define FALSE false
#define TRUE true


// Game logic
#define ROCK 'R'
#define PAPER 'P'
#define SCISSORS 'S'
#define WIN 'W'
#define LOOSE 'L'
#define DRAW 'D'
#define PLAYER_ONE '1'
#define PLAYER_TWO '2'


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


/*Initialising the matrix display*/
void init_tinygl (void)
{
    // Seting up tinygl
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (TEXT_SPEED);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    pacer_init (PACER_RATE);
}


///////////////////////////////////////////////////
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
///////////////////////////////////////////////////


/* Increments players choice in the games state, choice of PSR */
void choose_selection (state_t* game_state)
{
    navswitch_update ();
    if (game_state->selection_final == false) { /////////////////////////////////REMOVE THIS SOMEHOW

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
    }
}


/* Increments player number choice in the games state, choice of player1, player2 */
void select_player (state_t* game_state)
{

    navswitch_update ();  ////////////////////////////////////////////////////////////////////////////////////////////////////// remove

    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        game_state->player = PLAYER_ONE;
    }

    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        game_state->player = PLAYER_TWO;
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
		result = LOOSE;
	}
	
	state->round_result = result;
}

/* Inverts the result of a round */ 
void invert_result (state_t* game_state)
{
    if (game_state->round_result == WIN) {
        game_state->round_result = LOOSE;
    } 
    else if (game_state->round_result == LOOSE){
        game_state->round_result = WIN;
    }
}


/* Reset the game state for the next round */
void reset_game (state_t* game_state)
{
    game_state->player_selection = PAPER;
    game_state->opponent_selection = INIT_ZERO;
    game_state->selection_final = false;
    game_state->round_result = INIT_ZERO;
    game_state->confirm_selection = INIT_ZERO;
    game_state->result_set = false;
    game_state->sent = false;
    game_state->game_over = false;
}

/* Attempts to receive opponents choice, if successfull returns true */
void get_opponent(state_t* game_state)
{
    uint8_t read_choice;
    read_choice = receive_char();
    if(read_choice == 'R' || read_choice == 'S' || read_choice == 'P') {
        game_state->opponent_selection = read_choice;
    }
}

// Function to check if the results been received
void ir_rcv_result(state_t* game_state)
{
    uint8_t read_choice;
    read_choice = receive_char();
    if(read_choice == 'W' || read_choice == 'L' || read_choice == 'D') {
        game_state->round_result = read_choice;
        game_state->result_set = true;
    }
}



// Function to display the results
void display_result(state_t* game_state)
{
    if(game_state->game_over == false && game_state->sent) {

        if(game_state->round_result == 'W') {
            tinygl_text("WINNER");
        } else if (game_state->round_result == 'L') {
            tinygl_text("LOOSER");
        } else {
            tinygl_text("DRAW");
        }
        game_state->game_over = true;
    }
}


//Init game state
//parameter 
void init_player(state_t* game_state)
{
	game_state->player = PLAYER_ONE;
    game_state->player_selection = PAPER;
    game_state->opponent_selection = INIT_ZERO;
    game_state->selection_final = FALSE;
    game_state->round_result = INIT_ZERO;
    //score;
    game_state->confirm_selection = FALSE;
    game_state->result_set = FALSE;
    game_state->sent = FALSE;
    game_state->game_over = FALSE;
    game_state->player_selected = FALSE;	
}


int main (void)
{
    // Tick counter
    uint16_t tick = 0;
    
    
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
    state_t game_state = {'1','P',0,false,0,0,0,false, false, false, false};
    
    while(1) {
        
        // Checing for the state of the game
        bool start = 0;
        start = game_status(start);
        tinygl_update ();

        // Scrolling startup screen before game starts
        while (start == 0) {
            navswitch_update();
            pacer_wait ();
            tinygl_update ();
            break;
        }


        // Starting the game
        while (start == 1) {
            
            pacer_wait ();
            tinygl_update ();
            
            // Check if the player is selected
            if(game_state.player_selected == false) {
                select_player(&game_state);
                display_character (game_state.player);
                // Selects the player and clear the screen
				if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
					game_state.player_selected = true;
					tinygl_clear();
				}
                continue;
                
                
                

				
            } 
            else {
                // Restart loop if the player hasent selected     
                if(game_state.selection_final == false) {
                    choose_selection(&game_state);
                    display_character (game_state.player_selection);
					if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
						game_state.selection_final = true;
						tinygl_clear();
					}
                } 
                else {
                    navswitch_update();
                    // Player one
                    if(game_state.player == '1') {
                        get_opponent(&game_state);
                        // If the player 2 is available
                        if(game_state.opponent_selection != 0) {
                            if(game_state.result_set == false) {
                                // Check the results
                                get_result(&game_state);
                                game_state.result_set = true;
                            } 
                            else {
                                // Display the result
                                display_result(&game_state);
                            }
                        }
                    }

                    // Player two
                    if(game_state.player == '2') {
                        // Check if result is received
                        if(game_state.result_set == false) {
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

                        // Check if result is set
                        if (game_state.player == '1' && game_state.result_set) {
                            // Send result to player 2
                            if (game_state.sent == false) {
								game_state.sent = send_char (game_state.round_result);
							}
						}

                        if (game_state.player == '2') {
                            // Send selection to player 1
                            if (game_state.sent == false) {
								game_state.sent = send_char (game_state.player_selection);
							}
                        }


                    }


                }
            }
}
}
}

