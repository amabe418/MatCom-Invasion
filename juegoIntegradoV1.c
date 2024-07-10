#include <ncurses.h>   // Biblioteca para manejar la interfaz de consola
#include <pthread.h>   // Biblioteca para manejar hilos
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <stdlib.h>    // Biblioteca estándar de funciones generales
#include <unistd.h>    // Biblioteca para funciones POSIX como usleep
#include <time.h>      // Biblioteca para funciones de tiempo, como srand y time

// Estructura que representa a un enemigo
typedef struct {
    int x, y;   // Posición del enemigo en la pantalla (coordenadas x e y)
    int active; // Estado del enemigo (activo o no activo)
} Enemy;

// Constantes del juego
#define MAX_ENEMIES 10     // Número máximo de enemigos
#define PLAYER_SYMBOL '^'  // Símbolo que representa al jugador
#define ENEMY_SYMBOL 'X'   // Símbolo que representa a los enemigos
#define PROJECTILE_SYMBOL '|' // Símbolo que representa a los proyectiles
#define MAX_PROJECTILES 50 // Número máximo de proyectiles

Enemy enemies[MAX_ENEMIES];  // Arreglo de enemigos
int player_x, player_y;      // Posición del jugador
int score = 0;               // Puntuación del jugador

// Estructura que representa un proyectil
typedef struct {
    int x, y;   // Posición del proyectil en la pantalla (coordenadas x e y)
    int active; // Estado del proyectil (activo o no activo)
} Projectile;

Projectile projectiles[MAX_PROJECTILES]; // Arreglo de proyectiles

// Función para inicializar ncurses y la pantalla
void init() {
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

// Función para limpiar y finalizar ncurses
void cleanup() {
    endwin(); // Finaliza ncurses y restaura la configuración de la terminal
}

// Función para inicializar los enemigos
void initialize_enemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = 0; // Inicializa todos los enemigos como no activos
    }
}

// Función para calcular la próxima posición de aparición de un enemigo
int next_spawn_position() {
    static int last_position = 0; // Variable estática para mantener la última posición de aparición
    last_position = (last_position + 1) % COLS; // Incrementa la posición de aparición de manera circular
    return last_position; // Devuelve la nueva posición de aparición
}

// Función para hacer aparecer un nuevo enemigo
void spawn_enemy() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) { // Encuentra un enemigo inactivo
            enemies[i].x = next_spawn_position(); // Asigna la posición x de aparición
            enemies[i].y = 0;                     // Inicializa la posición y en la parte superior
            enemies[i].active = 1;                // Marca al enemigo como activo
            break; // Sale del bucle después de activar un enemigo
        }
    }
}

// Función para mover los enemigos
void move_enemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) { // Si el enemigo está activo
            enemies[i].y++;      // Incrementa la posición y (baja un lugar)
            if (enemies[i].y >= LINES) { // Si el enemigo llega al final de la pantalla
                //enemies[i].active = 0;   // Lo desactiva
                // Condición de derrota
                mvprintw(LINES / 2, COLS / 2 - 5, "Game Over!"); // Muestra el mensaje de derrota
                refresh(); // Actualiza la pantalla
                sleep(2);  // Pausa de 2 segundos
                cleanup(); // Finaliza ncurses
                exit(0);   // Termina el programa
            }
        }
    }
}

// Función para mover al jugador
void move_player(int ch) {
    switch (ch) {
        case KEY_UP:
            if (player_y > 0) player_y--; // Mueve al jugador hacia arriba si no está en el borde superior
            break;
        case KEY_DOWN:
            if (player_y < LINES - 1) player_y++; // Mueve al jugador hacia abajo si no está en el borde inferior
            break;
        case KEY_LEFT:
            if (player_x > 0) player_x--; // Mueve al jugador hacia la izquierda si no está en el borde izquierdo
            break;
        case KEY_RIGHT:
            if (player_x < COLS - 1) player_x++; // Mueve al jugador hacia la derecha si no está en el borde derecho
            break;
    }
}

// Función para disparar un proyectil
void shoot_projectile() {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (!projectiles[i].active) { // Encuentra un proyectil inactivo
            projectiles[i].x = player_x; // Asigna la posición x del proyectil a la del jugador
            projectiles[i].y = player_y - 1; // Asigna la posición y del proyectil justo encima del jugador
            projectiles[i].active = 1; // Marca el proyectil como activo
            break; // Sale del bucle después de activar un proyectil
        }
    }
}

// Función para mover los proyectiles
void move_projectiles() {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].active) { // Si el proyectil está activo
            projectiles[i].y = projectiles[i].y-2 ; // Decrementa la posición y (sube un lugar)
            if (projectiles[i].y < 0) { // Si el proyectil sale de la pantalla
                projectiles[i].active = 0; // Lo desactiva
            }
        }
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

// Función para actualizar la pantalla
void update_screen() {
    clear(); // Limpia la pantalla
    // Dibuja al jugador
    //mvaddch(player_y, player_x, PLAYER_SYMBOL);
    mvprintw(player_y, player_x, "%c", PLAYER_SYMBOL);

    // Dibuja los enemigos
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) { // Si el enemigo está activo
            mvprintw(enemies[i].y, enemies[i].x,"%c", ENEMY_SYMBOL); // Dibuja al enemigo
        }
    }

    // Dibuja los proyectiles
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].active) { // Si el proyectil está activo
            mvprintw(projectiles[i].y, projectiles[i].x, "%c",PROJECTILE_SYMBOL); // Dibuja el proyectil
        }
    }

    // Dibuja la puntuación
    mvprintw(0, 0, "Score: %d", score); // Muestra la puntuación en la esquina superior izquierda

    refresh(); // Actualiza la pantalla
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
