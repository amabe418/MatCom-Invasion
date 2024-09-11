#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "ScreenDesign.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include "global.h"
#include <locale.h>
#include "ScreenShows.h"
#include <ncurses.h>
#include "Records.h"
#include "juegoIntegradoV1.h"
#include <string.h>
#include "SoundEffect.h"


void start_screen()
{
    pthread_mutex_lock(&input_mutex);
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    start_color();  // Habilita el uso de colores
    // Define los pares de colores (color de texto, color de fondo)
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);

    int selected = 0; // 0 para "Jugar", 1 para "Salir"

    while (1)
    {
        clear();
        mvprintw(0, START_WINDOW, "SCORE: %d", score);
        mvprintw(0, MIDDLE_WINDOW - (strlen("HIGHEST SCORE")/2), "HIGHEST SCORE: %d", high_score);
        mvprintw(0, HORIZONTAL_END_WINDOW, "LIVES: %d", 5);
        // Muestra las opciones con el resaltado en la opción seleccionada
        if (selected == 0)
        {
            attron(COLOR_PAIR(4)| A_BOLD);
            mvprintw(LINES / 2 - 1, MIDDLE_WINDOW, "> JUGAR");
            attron(COLOR_PAIR(4)| A_BOLD);
            attron(COLOR_PAIR(4));
            mvprintw(LINES / 2 + 1, MIDDLE_WINDOW, "  SALIR");
            attroff(COLOR_PAIR(4));
        }
        else
        {
            attron(COLOR_PAIR(4));
            mvprintw(LINES / 2 - 1, MIDDLE_WINDOW, "  JUGAR");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(4)|A_BOLD);
            mvprintw(LINES / 2 + 1, MIDDLE_WINDOW, "> SALIR");
            attroff(COLOR_PAIR(4)|A_BOLD);
        }

        refresh();

        // Espera a que se presione una tecla
        int ch = getch();

        if (ch == KEY_DOWN)
        {
            selected = 1; // Cambia a "Salir"
        }
        else if (ch == KEY_UP)
        {
            selected = 0; // Cambia a "Jugar"
        }
        else if (ch == '\n')
        {
            break; // Presiona Enter para seleccionar
        }
    }

    // Limpia la pantalla de inicio
    clear();
    refresh();

    // Ejecuta la opción seleccionada
    if (selected == 0)
    {
        // Lógica para la opción "Jugar"
        mvprintw(LINES / 2, MIDDLE_WINDOW, "INICIANDO EL JUEGO...");
        refresh();
        sleep(1);
        clear();
        // getch();
    }
    else
    {
        // Lógica para la opción "Salir"
        mvprintw(LINES / 2, MIDDLE_WINDOW, "SALIENDO DEL JUEGO...");
        refresh(); // Actualiza la pantalla
        sleep(1);
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
    }

    endwin();
    pthread_mutex_unlock(&input_mutex);
}


void end_screen()
{
    playBackgroundSound(1);
    pthread_mutex_lock(&input_mutex);
    // nodelay(stdscr, FALSE); // Desactiva el modo no bloqueante
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    high_score = load_high_score();
    int selected = 0; // 0 para "Jugar", 1 para "Salir"
    int last_selected = -1;  // Guarda la última opción seleccionada

while (1)
{
    // Solo redibuja si ha cambiado la opción seleccionada
    if (selected != last_selected)
    {
        clear();
        mvprintw(0, START_WINDOW, "SCORE: %d", score);
        mvprintw(0, MIDDLE_WINDOW - (strlen("HIGHEST SCORE")/2), "HIGHEST SCORE: %d", high_score);
        mvprintw(0, HORIZONTAL_END_WINDOW, "LIVES: %d", lives);

        if (selected == 0)
        {
            attron(A_BOLD);
            mvprintw(LINES / 2 - 1, MIDDLE_WINDOW, "> REINICIAR");
            attroff(A_BOLD);
            mvprintw(LINES / 2 + 1, MIDDLE_WINDOW, "  SALIR");
        }
        else
        {
            mvprintw(LINES / 2 - 1, MIDDLE_WINDOW, "  REINICIAR");
            attron(A_BOLD);
            mvprintw(LINES / 2 + 1, MIDDLE_WINDOW, "> SALIR");
            attroff(A_BOLD);
        }

        refresh();
        last_selected = selected;  // Actualiza el valor de la opción seleccionada
    }

    int ch = getch();

    if (ch == KEY_DOWN)
    {
        selected = 1;
    }
    else if (ch == KEY_UP)
    {
        selected = 0;
    }
    else if (ch == '\n')
    {
        break;
    }
}

    // Limpia la pantalla de inicio
    clear();
    refresh();

    // Ejecuta la opción seleccionada
    if (selected == 0)
    {
        // Lógica para la opción "Jugar"
        mvprintw(LINES / 2, MIDDLE_WINDOW- MIDDLE_WINDOW/4, "REINICIANDO EL JUEGO...");
        refresh();
        sleep(1);
        pthread_mutex_unlock(&input_mutex);
        game_over = 0; // Reiniciar el juego
        clear();
        pthread_t game_thread;
        high_score = load_high_score(); // Cargar el récord guard

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
    }
    else
    {
        pthread_mutex_unlock(&input_mutex);
        // Lógica para la opción "Salir"
        mvprintw(LINES / 2, MIDDLE_WINDOW - MIDDLE_WINDOW/4, "SALIENDO DEL JUEGO...");
        refresh(); // Actualiza la pantalla
        sleep(1);
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
        // pthread_mutex_unlock(&input_mutex);
    }

    endwin();
}


/*


░░█ █░█ █▀▀ ▄▀█ █▀█
█▄█ █▄█ █▄█ █▀█ █▀▄


░░░░░██╗██╗░░░██╗░██████╗░░█████╗░██████╗░
░░░░░██║██║░░░██║██╔════╝░██╔══██╗██╔══██╗   X
░░░░░██║██║░░░██║██║░░██╗░███████║██████╔╝
██╗░░██║██║░░░██║██║░░╚██╗██╔══██║██╔══██╗
╚█████╔╝╚██████╔╝╚██████╔╝██║░░██║██║░░██║
░╚════╝░░╚═════╝░░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝


░░░▒█ ▒█░▒█ ▒█▀▀█ ░█▀▀█ ▒█▀▀█ 
░▄░▒█ ▒█░▒█ ▒█░▄▄ ▒█▄▄█ ▒█▄▄▀            X
▒█▄▄█ ░▀▄▄▀ ▒█▄▄█ ▒█░▒█ ▒█░▒█



───░█ ░█─░█ ░█▀▀█ ─█▀▀█ ░█▀▀█ 
─▄─░█ ░█─░█ ░█─▄▄ ░█▄▄█ ░█▄▄▀                X
░█▄▄█ ─▀▄▄▀ ░█▄▄█ ░█─░█ ░█─░█



█▀ ▄▀█ █░░ █ █▀█
▄█ █▀█ █▄▄ █ █▀▄



█▀█ █▀▀ █ █▄░█ █ █▀▀ █ ▄▀█ █▀█
█▀▄ ██▄ █ █░▀█ █ █▄▄ █ █▀█ █▀▄


*/