/** @file   game_type.h
    @authors  Lewis Garton, Janitha Gunathhilake
    @date   19 Oct 2017
    @brief  Include structures for the game states


    This module implements simple structures for the game states
    * and game results. Which is used by the main program to dermine
    * the state of the game. 
*/


#ifndef GAME_TYPES_H
#define GAME_TYPES_H


// struct for game state, 'N' indicates unselected
typedef struct{
    uint8_t player;
    uint8_t player_selection;
    uint8_t opponent_selection;
    bool selection_final;
    uint8_t round_result;
    int score;
    uint8_t confirm_selection;
    bool result_set;
    bool sent;
    bool game_over;
    bool player_selected;
} state_t;

// enums for the player variables
typedef enum {
    PAPER = 0,
    SCISSORS = 1,
    ROCK = 2,
    NONE = -1
} choice_t;

// enum for result
typedef enum {
    WIN,
    LOSE,
    DRAW,
    UNKNOWN = -1
} result_t;

#endif
