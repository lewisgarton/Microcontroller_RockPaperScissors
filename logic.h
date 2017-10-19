/** @file    logic.h
    @authors Janitha Gunathhilake, Lewis Garton
    @date    19 Oct 2017
    @brief   Provides required logic to run the game.

    Module contains the game logic for the paper, scissor rock game..
*/

#ifndef LOGIC_H
#define LOGIC_H
#include "game_types.h"

/*Function to check the state of the game*/
int game_status (void);


/* Displays character on the led matrix */
void display_character (char character);


/* Increments players choice in the games state, choice of PSR */
void choose_selection (state_t* game_state);


/* Increments player number choice in the games state, choice of player1, player2
 * If nav button is pressed, indicated selection chosen */
void select_player (state_t* game_state);


/* Computes the result of the game and stores in game state result */
void get_result (state_t* state);


/* Inverts the result of a round */
void invert_result (state_t* game_state);


/* Function to display the results */
void display_result(state_t* game_state);

#endif
