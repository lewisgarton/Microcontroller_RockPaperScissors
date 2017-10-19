##Overview

This program complies and run a paper, scissor, rock game on a ATmega32u2 microcontroller. The purpose of this 
game is to select a game variable from the given list and beat the other player. Each game variable is a given weight 
and the program compare these to decide the winner. 

##Game instructions

To play the game first move the navigation switch to either EAST or WEST. This will terminate the scrolling
instruction display and give a choice to select the player number. To select the player number use the 
EAST or WEST navigation button to iterate though the list and press down to select the player.

Game variables can be choosen by iterating through the displayed list containing Paper, scissors, Rock 
using the NORT and SOUTH buttons of the navigation switch.

Once the choice of game variable is visible in the display, that choice can be finalised by pressing down on the navigation switch.

The IR communication module will exchange the player choices and compare them to determine the winner, looser or if the game was a draw.

Once the winner, looser or draw is determined, apropriate message discribing the winner or looser will be visible on the UCFK display. 


##Authors

Janitha Gunathilake
Lewis Garton

##Date

19 Oct 2017

## Acknowledgment

Dr. Richard Clare
Dr. Michael Hayes






