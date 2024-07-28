#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include <pthread.h>   // Biblioteca para manejar hilos
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time
#include "ScreenDesign.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include "global.h"


// Función para actualizar la pantalla
void update_screen() {
    clear(); // Limpia la pantalla
    // Dibuja al jugador
    //mvaddch(player_y, player_x, PLAYER_SYMBOL);
    mvprintw(player_y, player_x, "%c", PLAYER_SYMBOL);

    // Dibuja los enemigos
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) { // Si el enemigo está activo
            mvprintw(enemies[i].y, enemies[i].x,"%c", ENEMY_SYMBOL); // Dibuja al enemigo
        }
    }

    // Dibuja los proyectiles
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].active) { // Si el proyectil está activo
            mvprintw(projectiles[i].y, projectiles[i].x, "%c",PROJECTILE_SYMBOL); // Dibuja el proyectil
        }
    }

    // Dibuja la puntuaciónf
    mvprintw(0, 0, "Score: %d", score); // Muestra la puntuación en la esquina superior izquierda

    refresh(); // Actualiza la pantalla
}
