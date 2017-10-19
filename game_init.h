/** @file    game_init.h
    @authors Janitha Gunathhilake, Lewis Garton
    @date    19 Oct 2017
    @brief   Initialization functions for paper scissors rock game

    initializes required programs/modules required for the game.
*/


#ifndef GAME_INIT_H
#define GAME_INIT_H
#include "game_types.h"

/*Initialising the matrix display*/
void init_tinygl (void);


/* Reset the game state for the next round */
void reset_game (state_t* game_state);


/* Init game state */
void init_player(state_t* game_state);

#endif
