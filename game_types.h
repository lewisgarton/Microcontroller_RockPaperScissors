/** @file   game_type.h
    @authors  Lewis Garton, Janitha Gunathhilake
    @date   19 Oct 2017
    @brief  Include structures and macros for the game states


    This module implements simple structures for the game states
    * and game results. Which is used by the main program to dermine
    * the state of the game. 
*/


#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#define PACER_RATE 300
#define MESSAGE_RATE 10
#define TEXT_SPEED 30


// Game State defaults
#define INIT_ZERO 0
#define FALSE false
#define TRUE true


// Game logic
#define NUMBER_OF_CHOICES 3
#define ROCK 'R'
#define PAPER 'P'
#define SCISSORS 'S'
#define NUMBER_OF_RESULTS 3
#define WIN 'W'
#define LOSE 'L'
#define DRAW 'D'
#define PLAYER_ONE '1'
#define PLAYER_TWO '2'


// struct for game state, 'N' indicates unselected
typedef struct{
    uint8_t player;
    uint8_t player_selection;
    uint8_t opponent_selection;
    bool selection_final;
    uint8_t round_result;
    uint8_t confirm_selection;
    bool result_set;
    bool sent;
    bool game_over;
    bool player_selected;
    bool game_started;
} state_t;


#endif
