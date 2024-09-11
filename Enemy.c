#include "Enemy.h"
#include "global.h"
#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time
#include "ScreenDesign.h"
#include "ScreenShows.h"


#define MAX_POSITIONS 10
int clock_hand = 0;// guarda la posicion siguiente a la ultima posicion ocupada
int position_state[MAX_POSITIONS] = {0}; // 0: unused, 1: used, 2: ready to be reused
int initial_position[10];

// Función para actualizar el array
void actualizarArray(int primerValor) {
    initial_position[0] = START_WINDOW + primerValor; // Asignar el primer valor
    for (int i = 1; i < MAX_POSITIONS; i++) {
        initial_position[i] = initial_position[i - 1] + 7; // Cada valor es el anterior más 7
    }
}


// int next_spawn_position() {
   
//     return START_WINDOW + rand() % (TOTAL_WIDTH-5); // Genera una posición aleatoria dentro del rango fijo
// }

int next_spawn_position() {
        // Generate a random position between 1 and 10
        int pos = rand() % MAX_POSITIONS;

        // If the position is unused, use it and mark it as used
        if (position_state[pos] == 0) {
            position_state[pos] = 1;
            return pos;
        }
        // If the position is used, check its state with the clock algorithm
        while(true)
        {
            clock_hand = (clock_hand + 1) % MAX_POSITIONS; //esto es para garantizar que nunca pase de 10 el valor de clockhand
            if (position_state[clock_hand] == 1) {
                position_state[clock_hand] = 0; // Reset to unused
            } else if (position_state[clock_hand] == 0) {
                position_state[clock_hand] = 1; // Move to the next state
                return clock_hand; // Return the position
            }
        }

}

// Nueva función para ajustar la posición de los enemigos según el redimensionamiento de la pantalla
void adjust_enemy_positions() {
    for (int i = 0; i < MAX_ENEMIES; i++) {                     
        if (enemies[i].active) {
            // Recalcular posiciones relativas aquí si es necesario
            enemies[i].x = (enemies[i].x - old_START_WINDOW + START_WINDOW); // Ajusta la posición x
            enemies[i].y = (enemies[i].y - (old_lines/2) + (LINES/2)); // Ajusta la posición y
        }
    }

        for (int i = 0; i < MAX_POSITIONS; i++) {
        initial_position[i] = initial_position[i] - old_START_WINDOW + START_WINDOW; // Reestructurando el array de posiciones iniciales posibles de los enemigos
    }
}
// Función para hacer aparecer un nuevo enemigo
void spawn_enemy() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) { // Encuentra un enemigo inactivo
            int position = next_spawn_position();
            // if(position==1)
            // {
            //     actualizarArray(rand()%7);
            // }
            enemies[i].x = initial_position[position]; // Asigna la posición x de aparición
            enemies[i].y = 3.0;                     // Inicializa la posición y en la parte superior
            enemies[i].active = 1;                // Marca al enemigo como activo
            break; // Sale del bucle después de activar un enemigo
        }
    }
}

// Función para mover los enemigos
void move_enemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) { // Si el enemigo está activo
            enemies[i].y+=0.4;      // Incrementa la posición y (baja un lugar)
            if (enemies[i].y >= LINES-ENEMY_WIDTH+1) { // Si el enemigo llega al final de la pantalla
                enemies[i].active = 0;   // Lo desactiva
                lives-=1;
                if(lives==0){
                game_over=0;
                end_screen();
                }
            }
        }
    }
}
