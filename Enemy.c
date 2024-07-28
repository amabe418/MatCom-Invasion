#include "Enemy.h"
#include "global.h"
#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time

// Función para inicializar los enemigos
void initialize_enemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = 0; // Inicializa todos los enemigos como no activos
    }
}

int next_spawn_position() {
    int range_start = COLS / 3;       // Inicio del rango fijo
    int range_end = 2 * COLS / 3;     // Fin del rango fijo
    int range_width = range_end - range_start;
    
    return range_start + rand() % range_width; // Genera una posición aleatoria dentro del rango fijo
}

// Función para hacer aparecer un nuevo enemigo
void spawn_enemy() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) { // Encuentra un enemigo inactivo
            enemies[i].x = next_spawn_position(); // Asigna la posición x de aparición
            enemies[i].y = 0;                     // Inicializa la posición y en la parte superior
            enemies[i].active = 1;                // Marca al enemigo como activo
            break; // Sale del bucle después de activar un enemigo
        }
    }
}

// Función para mover los enemigos
void move_enemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) { // Si el enemigo está activo
            enemies[i].y++;      // Incrementa la posición y (baja un lugar)
            if (enemies[i].y >= LINES) { // Si el enemigo llega al final de la pantalla
                //enemies[i].active = 0;   // Lo desactiva
                // Condición de derrota
                mvprintw(LINES / 2, COLS / 2 - 5, "Game Over!"); // Muestra el mensaje de derrota
                refresh(); // Actualiza la pantalla
                sleep(2);  // Pausa de 2 segundos
                cleanup(); // Finaliza ncurses
                exit(0);   // Termina el programa
            }
        }
    }
}
