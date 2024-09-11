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
#include "Bomb.h"
#include "Life.h"

WINDOW *screen_buffer;

void init_screen_buffer() {
    // screen_buffer = newwin(GAME_HEIGHT, TERMINAL_WIDTH, GAME_START_Y, GAME_START_X);
        screen_buffer = newwin(LINES, 200, GAME_START_Y, GAME_START_X);
}

void update_screen() {
    start_color();  // Habilita el uso de colores
    // Define los pares de colores (color de texto, color de fondo)
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);

    werase(screen_buffer); // Limpia el búfer

    wattron(screen_buffer, COLOR_PAIR(3) | A_BOLD);  // Color CYAN y negrita
    mvwprintw(screen_buffer, 0, START_WINDOW, "SCORE: %d", score);
    mvwprintw(screen_buffer, 0, MIDDLE_WINDOW, "HIGHEST SCORE: %d", high_score);
    mvwprintw(screen_buffer, 0, HORIZONTAL_END_WINDOW, "LIVES: %d", lives);
    wattroff(screen_buffer, COLOR_PAIR(3) | A_BOLD);  // Apaga el color y negrita

    //Dibuja al jugador
    wattron(screen_buffer, COLOR_PAIR(2) | A_BOLD);  // Color AMARILLO y negrita
    for (int i = 0; i < PLAYER_HEIGHT; i++) {
        mvwprintw(screen_buffer, player_y + i, player_x + player_running, "%s", PLAYER_SYMBOL[i]);
    }
    wattroff(screen_buffer, COLOR_PAIR(2) | A_BOLD);  // Apaga el color y negrita


   // Dibuja los enemigos
     wattron(screen_buffer, COLOR_PAIR(4) | A_BOLD);  // color BLANCO negrita
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            for (int j = 0; j < ENEMY_HEIGHT; j++) {
                mvwprintw(screen_buffer, enemies[i].y + j, enemies[i].x, "%s", ENEMY_SYMBOL[j]);
            }
        }
    }
     wattroff(screen_buffer, COLOR_PAIR(4) | A_BOLD);  // Apaga el color y negrita

    
    // Dibuja los proyectiles
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].active) {
            mvwprintw(screen_buffer, projectiles[i].y, projectiles[i].x, "%s", PROJECTILE_SYMBOL);
        }
    }
    
    //Dibuja las bombas
     wattron(screen_buffer, COLOR_PAIR(1) | A_BOLD);  // color BLANCO negrita
     for (int i = 0; i < numPowerups; i++) {
        if (powerups[i].active)
        {   
            mvwprintw(screen_buffer, powerups[i].y ,powerups[i].x, "%s", BOMB_SYMBOL);
        }
        
    }
     wattroff(screen_buffer, COLOR_PAIR(1) | A_BOLD);  // Apaga el color y negrita

     //Dibuja las vidas
     wattron(screen_buffer, COLOR_PAIR(5) | A_BOLD);  // color BLANCO negrita
     for (int i = 0; i < numLives; i++) {
        if (livesBomb[i].active)
        {   
            mvwprintw(screen_buffer, livesBomb[i].y ,livesBomb[i].x, "%s", LIFE_SYMBOL);
        }
        
    }
     wattroff(screen_buffer, COLOR_PAIR(5) | A_BOLD);  // Apaga el color y negrita
    
    // Refresca el búfer a la pantalla real
    wnoutrefresh(screen_buffer);
    doupdate();
}



