#include "global.h"
#include "global.h"

// Función para limpiar y finalizar ncurses
void cleanup() {
    endwin(); // Finaliza ncurses y restaura la configuración de la terminal
}
// global variables  definition

Projectile projectiles[MAX_PROJECTILES]; // Arreglo de proyectiles
int player_x, player_y;      // Posición del jugador
int score;               // Puntuación del jugador
Enemy enemies[MAX_ENEMIES];  // Arreglo de enemigos
GameObject powerups[5];
GameObject livesBomb[5];
int game_over;
int high_score;
int lives;
int player_running;
int old_START_WINDOW;
int old_cols_player;
int old_lines;
int numPowerups;
int numLives;
// Variables globales
pthread_mutex_t game_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t input_mutex = PTHREAD_MUTEX_INITIALIZER;