#include "Projectile.h"
#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time
#include "Player.h"
#include "global.h"
// Función para disparar un proyectil
void shoot_projectile() {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (!projectiles[i].active) { // Encuentra un proyectil inactivo
            projectiles[i].x = player_x; // Asigna la posición x del proyectil a la del jugador
            projectiles[i].y = player_y - 1; // Asigna la posición y del proyectil justo encima del jugador
            projectiles[i].active = 1; // Marca el proyectil como activo
            break; // Sale del bucle después de activar un proyectil
        }
    }

}

// Función para mover los proyectiles
void move_projectiles() {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].active) { // Si el proyectil está activo
            projectiles[i].y = projectiles[i].y-2 ; // Decrementa la posición y (sube un lugar)
            if (projectiles[i].y < 0) { // Si el proyectil sale de la pantalla
                projectiles[i].active = 0; // Lo desactiva
            }
        }
    }
}

