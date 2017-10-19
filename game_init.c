/** @file    game_init.c
    @authors Janitha Gunathhilake, Lewis Garton
    @date    19 Oct 2017
    @brief   Initialization functions for paper scissors rock game

    initializes required programs/modules required for the game.
*/


#include "game_init.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"


/* Initialising the matrix display */
void init_tinygl (void)
{
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (TEXT_SPEED);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    pacer_init (PACER_RATE);
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


/* Initialising the game states */
void init_player(state_t* game_state)
{
    game_state->player = PLAYER_ONE;
    game_state->player_selection = PAPER;
    game_state->opponent_selection = INIT_ZERO;
    game_state->selection_final = FALSE;
    game_state->round_result = INIT_ZERO;
    game_state->confirm_selection = FALSE;
    game_state->result_set = FALSE;
    game_state->sent = FALSE;
    game_state->game_over = FALSE;
    game_state->player_selected = FALSE;
    game_state->game_started = FALSE;
}
