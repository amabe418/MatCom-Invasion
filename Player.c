#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include <pthread.h>   // Biblioteca para manejar hilos
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time
#include "Player.h"
#include "global.h"


// Función para mover al jugador
void move_player(int ch) {
    switch (ch) {
        case KEY_UP:
            if (player_y > 0) player_y--; // Mueve al jugador hacia arriba si no está en el borde superior
            break;
        case KEY_DOWN:
            if (player_y < LINES - 1) player_y++; // Mueve al jugador hacia abajo si no está en el borde inferior
            break;
        case KEY_LEFT:
            if (player_x > 0) player_x--; // Mueve al jugador hacia la izquierda si no está en el borde izquierdo
            break;
        case KEY_RIGHT:
            if (player_x < COLS - 1) player_x++; // Mueve al jugador hacia la derecha si no está en el borde derecho
            break;
    }
}
