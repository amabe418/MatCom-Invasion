#include "Enemy.h"
#include "global.h"
#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time
#include "ScreenDesign.h"
#include "ScreenShows.h"


// Función para inicializar los enemigos
void initialize_enemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = 0; // Inicializa todos los enemigos como no activos
        enemies[i].symbol = "x";
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
            enemies[i].y = 1.0;                     // Inicializa la posición y en la parte superior
            enemies[i].active = 1;                // Marca al enemigo como activo
            break; // Sale del bucle después de activar un enemigo
        }
    }
}

// Función para mover los enemigos
void move_enemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) { // Si el enemigo está activo
            enemies[i].y+=0.5;      // Incrementa la posición y (baja un lugar)
            if (enemies[i].y >= LINES) { // Si el enemigo llega al final de la pantalla
                enemies[i].active = 0;   // Lo desactiva
                // Condición de derrota
                game_over=0;
                end_screen();
            }
        }
    }
}
