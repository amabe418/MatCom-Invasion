#ifndef GLOBAL
#define GLOBAL

#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include "Projectile.h"
#include "Enemy.h"

void cleanup();
// variables.h
extern Projectile projectiles[MAX_PROJECTILES]; // Arreglo de proyectiles
extern int player_x;
extern int player_y;
extern int score;
extern Enemy enemies[MAX_ENEMIES];  // Arreglo de enemigos
#endif 