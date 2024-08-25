#include "Projectile.h"
#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time
#include "Player.h"
#include "global.h"


// Función para mover los proyectiles
void move_projectiles() {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].active) { // Si el proyectil está activo
            projectiles[i].y = projectiles[i].y-1 ; // Decrementa la posición y (sube un lugar)
            if (projectiles[i].y < 0) { // Si el proyectil sale de la pantalla
                projectiles[i].active = 0; // Lo desactiva
            }
        }
    }
}

// Función para disparar proyectil
void *shoot_projectile(void *arg)
{
    pthread_mutex_lock(&game_mutex);
    for (int i = 0; i < MAX_PROJECTILES; i++)
    {
        if (!projectiles[i].active)
        {
            projectiles[i].active = 1;
            projectiles[i].x = player_x;
            projectiles[i].y = player_y - 1;

            // Mover el cursor a la posición del proyectil y dibujarlo
            move(projectiles[i].y, projectiles[i].x);
            addch(PROJECTILE_SYMBOL); // Dibuja el proyectil
            break;
        }
    }
    pthread_mutex_unlock(&game_mutex);
    pthread_exit(NULL);
}

void detect_collisions()
{
    pthread_mutex_lock(&game_mutex);
    for (int i = 0; i < MAX_PROJECTILES; i++)
    {
        if (projectiles[i].active)
        {
            for (int j = 0; j < MAX_ENEMIES; j++)
            {
                if (enemies[j].active && abs(projectiles[i].x - enemies[j].x) <= RANGO && projectiles[i].y == enemies[j].y)
                {
                    projectiles[i].active = 0;
                    enemies[j].active = 0;
                    score++;
                }
            }
        }
    }
    pthread_mutex_unlock(&game_mutex);
}