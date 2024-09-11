#ifndef PROJECTILE_H
#define PROJECTILE_H

// Función para mover los proyectiles
void move_projectiles();
void *shoot_projectile(void *arg);
void detect_collisions();

#endif