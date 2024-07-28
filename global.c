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