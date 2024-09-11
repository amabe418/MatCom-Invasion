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
#include "Records.h"
#include <signal.h>
#include "Bomb.h"
#include "Life.h"

// // Prototipos de funciones
// void init();
// void detect_collisions();
// void *game_loop(void *arg);
// void handle_input();
// void init_screen_buffer(); // Prototipo de la función para inicializar el búfer doble

void handle_winch(int sig) {
    // Recalcular el tamaño de la pantalla
    old_START_WINDOW = START_WINDOW;
    old_cols_player = COLS/2;
    old_lines = LINES;
    endwin();
    refresh();
    clear();
    mvwin(screen_buffer, 0, COLS/3-10);
    // Actualizar posiciones relativas en función del nuevo tamaño de la terminal
    player_x = player_x- old_cols_player + COLS / 2;  // Recalcular la posición del jugador
    player_y = LINES - 3;

    // Ajustar las posiciones de los enemigos en base al nuevo tamaño
    adjust_enemy_positions();

    adjust_bomb_positions();

    adjust_Lives_positions();
    
    // Llamar a la función que redibuja la pantalla
    update_screen();
}

void init()
{

    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    signal(SIGWINCH, handle_winch);  // Configurar el manejador para SIGWINCH
    high_score = load_high_score(); // Cargar e récord guardo
    player_x = MIDDLE_WINDOW;
    player_y = LINES-3;
    score = 0;
    game_over = 0;
    lives = 5;
    player_running = 0;
    numPowerups = 0;
    numLives=0;
    for (int i = 0; i < MAX_PROJECTILES; i++)
    {
        projectiles[i].active = 0;
    }
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].active = 0;
    }
    for(int i=0; i<5; i++)
    {
        powerups[i].active = 0;
    }
    actualizarArray(rand()%7);
    // initPowerup();
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
          refresh(); // Actualiza la pantalla
       
         save_score(score);
         // Verifica si el puntaje actual es un nuevo récord
         if (score > high_score)
         {
            high_score = score;
            save_high_score(high_score);
         }
         cleanup(); // Finaliza ncurses
         endwin();
         exit(0); // Salir del programa
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
    const int enemy_spawn_threshold = 30; // Ajusta este valor para controlar la velocidad de los enemigos
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
        updatePowerups();
        initPowerup();
        updateLives();
        initLives();
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
    // Habilita el uso de colores
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
