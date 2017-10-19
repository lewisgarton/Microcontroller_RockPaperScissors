/** @file   game_type.h
    @authors  Lewis Garton, Janitha Gunathhilake
    @date   19 Oct 2017
    @brief  Include structures for the game states


    This module implements simple structures for the game states
    * and game results. Which is used by the main program to dermine
    * the state of the game. 
*/

#include "stdbool.h"
#include "ir_uart.h"


#define TRUE true
#define FALSE false

/* Sends a given message, if successful returns true */
bool send_char (char message)
{
	bool flag = FALSE;
	if (ir_uart_write_ready_p()) {
		ir_uart_putc(message);
	}

    if (ir_uart_write_finished_p()) {
		flag = TRUE;
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



