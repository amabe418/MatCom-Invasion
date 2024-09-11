#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include <pthread.h>   // Biblioteca para manejar hilos
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time
#include "Player.h"
#include "global.h"
#include "ScreenDesign.h"


// Función para mover al jugador
void *move_player(void *arg) {
    pthread_mutex_lock(&game_mutex);

    int direction = *((int *)arg);

    // Borrar la figura anterior del jugador
    for (int i = 0; i < PLAYER_HEIGHT; i++) {
        mvwprintw(screen_buffer, player_y + i, player_x + player_running, "        ");  // Borra la línea anterior
    }

    // Actualiza la posición del jugador
    if (direction == KEY_LEFT && player_x + player_running > START_WINDOW) {
        player_running--;
    } else if (direction == KEY_RIGHT && player_x + player_running < HORIZONTAL_END_WINDOW) {
        player_running++;
    }

    // Dibuja la nueva figura del jugador en la nueva posición
    wattron(screen_buffer, COLOR_PAIR(2) | A_BOLD);  // Activa el color y negrita
    for (int i = 0; i < PLAYER_HEIGHT; i++) {
        mvwprintw(screen_buffer, player_y + i, player_x + player_running+PLAYER_WIDTH/2, "%s", PLAYER_SYMBOL[i]);
    }
    wattroff(screen_buffer, COLOR_PAIR(2) | A_BOLD);  // Desactiva el color y negrita

    pthread_mutex_unlock(&game_mutex);
    pthread_exit(NULL);
}

