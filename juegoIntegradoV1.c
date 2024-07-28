#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include "global.h"
#include <pthread.h>   // Biblioteca para manejar hilos
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time
#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include "ScreenDesign.h"


// Función para inicializar ncurses y la pantalla
void init() {
    srand(time(NULL));    // Inicializa la semilla para números aleatorios
    initscr();            // Inicializa la pantalla
    cbreak();             // Desactiva el buffer de línea
    noecho();             // No muestra los caracteres ingresados
    keypad(stdscr, TRUE); // Habilita el uso de teclas especiales
    curs_set(FALSE);      // Oculta el cursor
    player_x = COLS / 2;  // Inicializa la posición del jugador en el centro horizontal
    player_y = LINES - 2; // Inicializa la posición del jugador en la penúltima línea
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        projectiles[i].active = 0; // Inicializa todos los proyectiles como no activos
    }
}


// Función para detectar colisiones entre proyectiles y enemigos
void detect_collisions() {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].active) { // Si el proyectil está activo
            for (int j = 0; j < MAX_ENEMIES; j++) {
                if (enemies[j].active && projectiles[i].x == enemies[j].x && projectiles[i].y == enemies[j].y) {
                    // Si hay una colisión entre un proyectil y un enemigo activo
                    projectiles[i].active = 0; // Desactiva el proyectil
                    //enemies[j].active = 0; // Desactiva el enemigo
                    score++; // Incrementa la puntuación
                }
            }
        }
    }
}


// Función para escuchar eventos de teclado
void *listen_events(void *arg) {
    int ch;
    while ((ch = getch()) != 'q') { // Escucha teclas hasta que se presiona 'q'
        switch (ch) {
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                move_player(ch); // Mueve al jugador
                break;
            case ' ':
                shoot_projectile(); // Dispara un proyectil
                break;
        }
    }
    pthread_exit(NULL); // Termina el hilo
}

// Función para manejar la lógica del juego
void *game_logic(void *arg) {
    while (1) {
        spawn_enemy(); // Aparece un nuevo enemigo
        move_enemies(); // Mueve los enemigos
        move_projectiles(); // Mueve los proyectiles
        detect_collisions(); // Detecta colisiones
        update_screen(); // Actualiza la pantalla
        usleep(500000); // Pausa de medio segundo
    }
    pthread_exit(NULL); // Termina el hilo
}

// Función principal
int main() {
    pthread_t threads[2]; // Arreglo de dos hilos
    int rc;

    srand(time(NULL));  // Inicializa la semilla para números aleatorios
    init();  // Inicializa ncurses
    initialize_enemies();  // Inicializa enemigos

    // Crea un hilo para escuchar eventos
    rc = pthread_create(&threads[0], NULL, listen_events, NULL);
    if (rc) {
        printf("Error: unable to create thread, %d\n", rc);
        exit(-1);
    }

    // Crea un hilo para la lógica del juego
    rc = pthread_create(&threads[1], NULL, game_logic, NULL);
    if (rc) {
        printf("Error: unable to create thread, %d\n", rc);
        exit(-1);
    }

    // Espera a que los hilos terminen
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    cleanup();  // Finaliza ncurses
    return 0;
}
