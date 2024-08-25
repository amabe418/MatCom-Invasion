#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include <pthread.h>   // Biblioteca para manejar hilos
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time
#include "Player.h"
#include "global.h"


// Función para mover al jugador
void *move_player(void *arg)
{
    pthread_mutex_lock(&game_mutex);
    int direction = *((int *)arg);
    if (direction == KEY_LEFT && player_x > 0)
    {
        player_x--;
    }
    else if (direction == KEY_RIGHT && player_x < COLS - 1)
    {
        player_x++;
    }
    // Mover el cursor a la posición del proyectil y dibujarlo
    move(player_y, player_x);
    addch(PLAYER_SYMBOL); // Dibuja el jugador
    pthread_mutex_unlock(&game_mutex);
    pthread_exit(NULL);
}

