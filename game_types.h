


#ifndef GAME_TYPES_H
#define GAME_TYPES_H

// enum for player choice
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
