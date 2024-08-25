#ifndef GLOBAL
#define GLOBAL

#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include "Projectile.h"
#include "Enemy.h"
#include <pthread.h>
#define RANGO 5
#define GAME_WIDTH 500
#define GAME_HEIGHT 200
#define GAME_START_X 0
#define GAME_START_Y 0

void cleanup();
// variables.h
extern Projectile projectiles[MAX_PROJECTILES]; // Arreglo de proyectiles
extern int player_x;
extern int player_y;
extern int score;
extern int high_score;
extern Enemy enemies[MAX_ENEMIES];  // Arreglo de enemigos
extern int game_over; 
// Variables globales
extern pthread_mutex_t game_mutex;
extern pthread_mutex_t input_mutex;
#endif 