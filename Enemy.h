#ifndef ENEMY_H
#define ENEMY_H

#define MAX_ENEMIES 10     // Número máximo de enemigos
#define ENEMY_SYMBOL 'X'   // Símbolo que representa a los enemigos


// Estructura que representa a un enemigo
typedef struct {
    int x, y;   // Posición del enemigo en la pantalla (coordenadas x e y)
    int active; // Estado del enemigo (activo o no activo)
} Enemy;


// Función para inicializar los enemigos
void initialize_enemies();

// Función para calcular la próxima posición de aparición de un enemigo
int next_spawn_position();

// Función para hacer aparecer un nuevo enemigo
void spawn_enemy();

// Función para mover los enemigos
void move_enemies();











#endif 