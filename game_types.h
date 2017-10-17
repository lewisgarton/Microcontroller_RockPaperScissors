#ifndef GAME_TYPES_H
#define GAME_TYPES_H


// enum for player choice
typedef enum {
    ROCK,
    PAPER,
    SCISSORS,
    NONE = 0
} choice_t;

// enum for result
typedef enum {
    WIN,
    LOSE,
    DRAW,
    UNKNOWN = 0
} result_t;
