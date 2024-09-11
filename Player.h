#ifndef PLAYER_H
#define PLAYER_H

// Player.h

#define PLAYER_HEIGHT 3
#define PLAYER_WIDTH 8

// Declaración de la variable extern
extern const char *PLAYER_SYMBOL[PLAYER_HEIGHT];


void *move_player(void *arg);

#endif

/*
     ___
    /___\     
     /|\

     \ /
    T _ T
    /   \

   |_@_
    ||| \
    / \
 
     /\
   _/##\_
 /\|####|/\  nave

  
*/
