


#ifndef GAME_TYPES_H
#define GAME_TYPES_H




// struct for game state, 'N' indicates unselected
typedef struct{
    int player;
    uint8_t selection;
    uint8_t opponent;
    bool selection_final;
    uint8_t result;
    int score;
    uint8_t confirm_selection;
    bool result_set;
} state_t;


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
