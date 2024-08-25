#ifndef JUEGOINTEGRADORV1_H
#define JUEGOINTEGRADORV1_H
void *game_loop(void *arg);

void handle_input();

void detect_collisions();
void init();
#endif