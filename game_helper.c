#include "game_types.h"

result_t get_result(choice_t player, choice_t opponent) {
    result_t result =  UNKNOWN;
    if (player == opponent) {
        result = DRAW;
    } else if (player == ROCK && opponent == SCISSORS) {
        result = WIN;
    } else if (player == PAPER && opponent == ROCK){
        result = WIN;
    } else if (player == SCISSORS && opponent == PAPER) {
        result = WIN;
    } else {
        result = LOSE;
    }
    return result;
}
