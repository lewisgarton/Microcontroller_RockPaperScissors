/** @file     communication.h
    @authors  Lewis Garton, Janitha Gunathhilake
    @date     19 Oct 2017
    @brief    Provides comunications funcions

    This module implements simple communication functions required to 
    * run the state of the game. 
*/


#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H
#include "game_types.h"

/* Sends a given message, if successful returns true */
int send_char (char message);

    
/* Trys to receive a char, if fails returns 0 */
char receive_char (void);


/* Checks to see if a recieved character is the expected */
int receive_expected_char (int* character, char expected_list[], int list_length);


/* Gets the opponents choice */
void get_opponent(state_t* game_state);


/* Function to check if the results been received */
void ir_rcv_result(state_t* game_state);

#endif
