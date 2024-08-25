#ifndef PROJECTILE_H
#define PROJECTILE_H

#define PROJECTILE_SYMBOL '*' // Símbolo que representa a los proyectiles
#define MAX_PROJECTILES 50 // Número máximo de proyectiles

// Estructura que representa un proyectil
typedef struct {
    int x, y;   // Posición del proyectil en la pantalla (coordenadas x e y)
    int active; // Estado del proyectil (activo o no activo)
} Projectile;


// Función para mover los proyectiles
void move_projectiles();
void *shoot_projectile(void *arg);
void detect_collisions();

#endif