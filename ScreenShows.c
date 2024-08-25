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

void start_screen()
{
    pthread_mutex_lock(&input_mutex);
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    int selected = 0; // 0 para "Jugar", 1 para "Salir"

    while (1)
    {
        clear();
        mvprintw(0, 0, "SCORE: %d", score);
        mvprintw(0, 30, "HIGHEST SCORE: %d", high_score);
        mvprintw(0, 70, "LIVES: %d", 3);
        // Muestra las opciones con el resaltado en la opción seleccionada
        if (selected == 0)
        {
            attron(A_BOLD);
            mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "> JUGAR");
            attron(A_BOLD);
            mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "  SALIR");
        }
        else
        {
            mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "  JUGAR");
            attron(A_BOLD);
            mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "> SALIR");
            attron(A_BOLD);
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
        mvprintw(LINES / 2, (COLS - 20) / 2, "INICIANDO EL JUEGO...");
        refresh();
        sleep(1);
        clear();
        // getch();
    }
    else
    {
        // Lógica para la opción "Salir"
        mvprintw(LINES / 2, (COLS - 20) / 2, "SALIENDO DEL JUEGO...");
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

void pause_screen()
{
    pthread_mutex_lock(&input_mutex);
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    int selected = 0; // 0 para "Jugar", 1 para "Salir"

    while (1)
    {
        clear();
    // wprintw(screen_buffer,"holamundo");
        mvprintw(0, 0, "SCORE: %d", score);
        mvprintw(0, 30, "HIGHEST SCORE: %d", high_score);
        mvprintw(0, 70, "LIVES: %d", 3);
        // Muestra las opciones con el resaltado en la opción seleccionada
        if (selected == 0)
        {
            attron(A_BOLD);
            mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "> REANUDAR");
            attron(A_BOLD);
            mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "  SALIR");
        }
        else
        {
            mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "  REANUDAR");
            attron(A_BOLD);
            mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "> SALIR");
            attron(A_BOLD);
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
        mvprintw(LINES / 2, (COLS - 20) / 2, "REANUDANDO EL JUEGO...");
        refresh();
        sleep(1);
        clear();
        game_over = 0; // Reiniciar el juego
        endwin();
    }
    else
    {
        // Lógica para la opción "Salir"
        mvprintw(LINES / 2, (COLS - 20) / 2, "SALIENDO DEL JUEGO...");
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
    pthread_mutex_lock(&input_mutex);
    // nodelay(stdscr, FALSE); // Desactiva el modo no bloqueante
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    int selected = 0; // 0 para "Jugar", 1 para "Salir"

    // nodelay(stdscr, FALSE); // Desactiva el modo no bloqueante
    while (1)
    {
        clear();
        mvprintw(0, 0, "SCORE: %d", score);
        mvprintw(0, 30, "HIGHEST SCORE: %d", high_score);
        mvprintw(0, 70, "LIVES: %d", 3);
        mvprintw(LINES / 2 - 4, (COLS - 20) / 2, "JUEGO TERMINADO!");
        // Muestra las opciones con el resaltado en la opción seleccionada
        if (selected == 0)
        {
            attron(A_BOLD);
            mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "> REINICIAR");
            attron(A_BOLD);
            mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "  SALIR");
        }
        else
        {
            mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "  REINICIAR");
            attron(A_BOLD);
            mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "> SALIR");
            attron(A_BOLD);
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
    // nodelay(stdscr, TRUE); // Desactiva el modo no bloqueante

    // Limpia la pantalla de inicio
    clear();
    refresh();

    // Ejecuta la opción seleccionada
    if (selected == 0)
    {
        // Lógica para la opción "Jugar"
        mvprintw(LINES / 2, (COLS - 20) / 2, "REINICIANDO EL JUEGO...");
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
        mvprintw(LINES / 2, (COLS - 20) / 2, "SALIENDO DEL JUEGO...");
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
