#ifndef ENEMY_H
#define ENEMY_H

// Enemy.h
#define ENEMY_HEIGHT 3
#define ENEMY_WIDTH 7

// Declaración de la variable extern
extern const char *ENEMY_SYMBOL[ENEMY_HEIGHT];


void actualizarArray(int primerValor);


// Función para calcular la próxima posición de aparición de un enemigo
int next_spawn_position();

// Función para hacer aparecer un nuevo enemigo
void spawn_enemy();

// Función para mover los enemigos
void move_enemies();

//Funcion  para ajustar la posicion de los enemigos en la terminal
void adjust_enemy_positions();









#endif 