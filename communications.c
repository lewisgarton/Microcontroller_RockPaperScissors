/** @file     communication.c
    @authors  Lewis Garton, Janitha Gunathhilake
    @date     19 Oct 2017
    @brief    Provides comunications funcions

    This module implements simple communication functions required to
    * run the state of the game.
*/


#include "ir_uart.h"
#include "communications.h"


/* Sends a given message, if successful returns true */
int send_char (char message)
{
    int flag = 0;
    if (ir_uart_write_ready_p()) {
        ir_uart_putc(message);
    }

    if (ir_uart_write_finished_p()) {
        flag = 1;
    }
    return flag;
}


/* Trys to receive a char, if fails returns 0 */
char receive_char (void)
{
    char received = 0;
    if(ir_uart_read_ready_p()) {
        received = ir_uart_getc();
    }
    return received;

}


/* Checks to see if a recieved character is the expected*/
int receive_expected_char (int* character, char expected_list[], int list_length)
{
    int flag = 0;
    char received = receive_char();

    if (received) {
        int i;
        for (i = 0; i < list_length; i++) {
            if (received == expected_list[i]) {
                *character = received;
                flag = 1;
            }
        }
    }
    return flag;

}


/* Gets the opponents choice */
void get_opponent(state_t* game_state)
{
    int result_received = INIT_ZERO;
    char expected[NUMBER_OF_CHOICES] = {ROCK, PAPER, SCISSORS};

    if (receive_expected_char (&result_received, expected , NUMBER_OF_CHOICES)) {
        game_state->opponent_selection = result_received;
    }
}


/* Function to check if the results been received */
void ir_rcv_result(state_t* game_state)
{
    int result_received = INIT_ZERO;
    char expected[NUMBER_OF_RESULTS] = {WIN, LOSE, DRAW};

    if (receive_expected_char (&result_received, expected , NUMBER_OF_RESULTS)) {
        game_state->round_result = result_received;
        game_state->result_set = true;
    }
}
