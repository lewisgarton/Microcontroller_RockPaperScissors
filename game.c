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

#define PACER_RATE 300
#define MESSAGE_RATE 10
#define TEXT_SPEED 30



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
    // Sending the messasge to the display
    tinygl_text (message);

}

/*Initialising the matrix display*/
void my_matrix_init (void)
{
    // Seting up the tinygl library
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (TEXT_SPEED);
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

void choose_selection(state_t* game_state)
{
    navswitch_update ();
    if (game_state->selection_final == false) {

        // Scrolling right in the list
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (game_state->selection < 'S') {
                // Jump 2 if q, this needs to be changed once p,r,s defined as macros
                game_state->selection++;
                if(game_state->selection == 'Q') {
                    game_state->selection++;
                }
            }
        }

        // Scrolling left in the list
        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (game_state->selection > 'P') {
                // Jump 2 if q, this needs to be changed once p,r,s defined as macros
                game_state->selection--;
                if(game_state->selection == 'Q') {
                    game_state->selection--;
                }
            }
        }

        // Showing the current letter in the display
        display_character (game_state->selection);

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            game_state->selection_final = true;
            tinygl_clear();
        }
    }
}


void select_player(state_t* game_state){
	navswitch_update ();
	if (navswitch_push_event_p (NAVSWITCH_WEST)) {
		game_state->player = '1';
	}
	
	if (navswitch_push_event_p (NAVSWITCH_EAST)) {
		game_state->player = '2';
	}	
	
	display_character (game_state->player);
	
	if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            game_state->player_selected = true;
            tinygl_clear();
    }
}

// Send message
void snd_ir(state_t* game_state,uint8_t message)
{
	if(game_state->sent == false){	
		if(ir_uart_write_ready_p()) {
			ir_uart_putc(message);
		}
		
		if(ir_uart_write_finished_p()) {
			game_state->sent = true;
		}
	}
}


// Recieve message, if none return 0 else return ascii
uint8_t rcv_ir(void)
{
    uint8_t recived = 0;
    if(ir_uart_read_ready_p()) {
        recived = ir_uart_getc();
    }
    return recived;

}



void get_result(state_t* state) {
    if(state->result == 0) {
        char result;
        if (state->selection == state->opponent) {
            result = 'D';
        } else if (state->selection == 'R' && state->opponent == 'S') {
            result = 'W';
        } else if (state->selection == 'P' && state->opponent == 'R'){
            result = 'W';
        } else if (state->selection == 'S' && state->opponent == 'P') {
            result = 'W';
        } else {
            result = 'L';
        }
        state->result = result;
        state->result_set = true;
    }
}
void invert_result(state_t* game_state){
	if(game_state->result == 'D'){
		game_state->result = 'D';
	} else if (game_state->result == 'W') {
		game_state->result = 'L';
	} else {
		game_state->result = 'W';
	}	
}


// reset the game state to play again
void reset_game(state_t* game_state){
	game_state->selection = 'P';
	game_state->opponent = 0;
	game_state->selection_final = false;
	game_state->result = 0;
	game_state->confirm_selection = 0;
	game_state->result_set = false;
	game_state->sent = false;
	game_state->game_over = false;
	
	
	// clear display
	tinygl_clear();
	/*
	nt player;
    uint8_t selection;
    uint8_t opponent;
    bool selection_final;
    uint8_t result;
    int score;
    uint8_t confirm_selection;
    bool result_set;
	
	
	
	{0,'P',0,false,0,0,0,false};
	*/
}


void get_opponent(state_t* game_state){
        uint8_t read_choice;
        read_choice = rcv_ir();
        if(read_choice == 'R' || read_choice == 'S' || read_choice == 'P') {
            game_state->opponent = read_choice;
        }
    }

void ir_rcv_result(state_t* game_state){
        uint8_t read_choice;
        read_choice = rcv_ir();
        if(read_choice == 'W' || read_choice == 'L' || read_choice == 'D') {
            game_state->result = read_choice;
            game_state->result_set = true;
        }
    }




void display_result(state_t* game_state){
	if(game_state->game_over == false && game_state->sent){
		
		if(game_state->result == 'W') {
			display_string("WINNER");
		} else if (game_state->result == 'L') {
			display_string("LOOSER");
		} else {
			display_string("DRAW");		
		}
	game_state->game_over = true;	
	}
}





int main (void)
{	
    uint16_t tick = 0;
    // Arrays for selecting the game variables
    // Scrolling screen text
    char* scroll_screen = "SELECT PLAYER PRESS DOWN BUTTON";
    //bool chosen = false;

    // Initialising systems
    system_init ();
    // Initialising display driver
    my_matrix_init();
    // Initialising inputs
    navswitch_init();

    ir_uart_init ();

    // Displaying the scroll screen
    display_string(scroll_screen);


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
               
        
        
        while (start == 1) {
            pacer_wait ();
            tinygl_update ();
			if(game_state.player_selected == false){
				select_player(&game_state);
				continue;								
			}else {
			
				if(game_state.selection_final == false){				
					choose_selection(&game_state);
				} else {
					navswitch_update();
					if(game_state.player == '1'){                    
						get_opponent(&game_state);	
						if(game_state.opponent != 0) {
							if(game_state.result_set == false){
								get_result(&game_state);
							} else {
								display_result(&game_state);
							}					
						}				
					}	
				
				
					if(game_state.player == '2'){
						if(game_state.result_set == false){
							ir_rcv_result(&game_state);					
						} else {
							invert_result(&game_state);
							display_result(&game_state);
						}			
					}
						
						
									
					if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
							reset_game(&game_state);
			
						}
					

					tick++;
					if (tick > PACER_RATE / MESSAGE_RATE) {
						tick = 0;
						
						
						if(game_state.player == '1' && game_state.result_set){
							snd_ir(&game_state, game_state.result);						
						}
						
						if(game_state.player == '2'){
							snd_ir(&game_state, game_state.selection);							
						}
						

					}
				

				}
			}
		
}
}
}
