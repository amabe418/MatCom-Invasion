#include <ncurses.h>
#include "global.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include "ScreenDesign.h"
#include "ScreenShows.h"
#include "global.h"
#include "Records.h"

// // Prototipos de funciones
// void init();
// void detect_collisions();
// void *game_loop(void *arg);
// void handle_input();
// void init_screen_buffer(); // Prototipo de la función para inicializar el búfer doble


void init()
{

    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    high_score = load_high_score(); // Cargar el récord guardo
    player_x = COLS / 2;
    player_y = LINES - 2;
    score = 0;
    high_score = 0;
    game_over = 0;
    for (int i = 0; i < MAX_PROJECTILES; i++)
    {
        projectiles[i].active = 0;
    }
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].active = 0;
    }

    init_screen_buffer(); // Inicializa el búfer doble
}


void handle_input()
{
    int ch;
    while (1)
    {
        pthread_mutex_lock(&input_mutex);
        ch = getch();
        pthread_t thread;
        switch (ch)
        {
        case KEY_LEFT:
        case KEY_RIGHT:
        {
            int direction = ch;
            pthread_create(&thread, NULL, move_player, &direction);
            pthread_detach(thread);
            break;
        }
        case ' ':
        {
            pthread_create(&thread, NULL, shoot_projectile, NULL);
            pthread_detach(thread);
            break;
        }
        case 'q':
            pthread_mutex_unlock(&input_mutex);
            pthread_mutex_lock(&game_mutex);
            pause_screen();
                pthread_mutex_unlock(&game_mutex);
            break;
        }
        pthread_mutex_unlock(&input_mutex);
    }
}

void *game_loop(void *arg)
{
    int enemy_move_counter = 0;
    const int enemy_move_threshold = 10; // Ajusta este valor para controlar la velocidad de los enemigos
    int enemy_spawn_counter = 0;
    const int enemy_spawn_threshold = 20; // Ajusta este valor para controlar la velocidad de los enemigos
    while (1)
    {
        usleep(10000); // Controla la velocidad del juego

        move_projectiles(); // Llamada a función externa

        if (enemy_move_counter >= enemy_move_threshold)
        {
            move_enemies(); // Mueve los enemigos solo cuando el contador alcanza el umbral
            enemy_move_counter = 0;
        }
        else
        {
            enemy_move_counter++;
        }

        detect_collisions();
        if (enemy_spawn_counter >= enemy_spawn_threshold)
        {

            spawn_enemy(); // Llamada a función externa
            enemy_spawn_counter = 0;
        }
        else
        {
            enemy_spawn_counter++;
        }

        pthread_mutex_lock(&game_mutex);
        update_screen();
        pthread_mutex_unlock(&game_mutex);
    }
    return NULL;
}

int main()
{
    pthread_t game_thread;
    high_score = load_high_score(); // Cargar el récord guardo
    start_screen();
    init();

    // Crear un hilo para el bucle del juego
    pthread_create(&game_thread, NULL, game_loop, NULL);

    // Bucle principal para manejar la entrada del usuario
    while (!game_over)
    {
        handle_input();
    }

    // Esperar a que el hilo del juego termine (nunca debería suceder en este caso)
    pthread_join(game_thread, NULL);

    end_screen();

    endwin();

    return 0;
}
