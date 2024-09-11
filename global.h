#ifndef GLOBAL
#define GLOBAL

#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include "Projectile.h"
#include <pthread.h>

#define RANGO 6
#define GAME_WIDTH 500
#define GAME_HEIGHT 200
#define GAME_START_X 0
#define GAME_START_Y 0
#define MAX_ENEMIES 7     // Número máximo de enemigos


// Asumiendo que la terminal tiene un tamaño fijo para manejar 70 caracteres de ancho
#define TOTAL_WIDTH 70 // Ancho fijo total de la ventana
#define TERMINAL_WIDTH COLS // Ancho actual de la terminal
#define START_WINDOW ((TERMINAL_WIDTH - TOTAL_WIDTH) / 2) // Calcula la posición inicial centrada
#define HORIZONTAL_END_WINDOW (START_WINDOW + TOTAL_WIDTH - 5) // Calcula la posición final centrada
#define MIDDLE_WINDOW (START_WINDOW + TOTAL_WIDTH / 2) // Calcula la posición media para el "HIGHEST SCORE"

void cleanup();
// variables.h

// Estructura que representa a un enemigo
typedef struct {
    double x, y;   // Posición del enemigo en la pantalla (coordenadas x e y)
    double active; // Estado del enemigo (activo o no activo) 
    // const char* symbol[]; // Cambiado a const char* para soportar strings
  
} Enemy;

#define PROJECTILE_SYMBOL "||" // Símbolo que representa a los proyectiles
#define MAX_PROJECTILES 50 // Número máximo de proyectiles

// Estructura que representa un proyectil
typedef struct {
    int x, y;   // Posición del proyectil en la pantalla (coordenadas x e y)
    int active; // Estado del proyectfil (activo o no activo)
} Projectile;


typedef struct {
    float x, y;
    float speed;
    int active;
} GameObject;

extern GameObject powerups[5];
extern GameObject livesBomb[5];
extern Projectile projectiles[MAX_PROJECTILES]; // Arreglo de proyectiles
extern int player_x;
extern int player_y;
extern int score;
extern int high_score;
extern Enemy enemies[MAX_ENEMIES];  // Arreglo de enemigos

extern int game_over; 
extern int lives;
extern int player_running;
extern int enemy_running;
extern int old_START_WINDOW;
extern int old_lines;
extern int old_cols_player;
extern int numPowerups;
extern int numLives;
// Variables globales
extern pthread_mutex_t game_mutex;
extern pthread_mutex_t input_mutex;
#endif 
