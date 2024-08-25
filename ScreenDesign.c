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



WINDOW *screen_buffer;

void init_screen_buffer() {
    screen_buffer = newwin(GAME_HEIGHT, GAME_WIDTH, GAME_START_Y, GAME_START_X);
}

void update_screen() {
    werase(screen_buffer); // Limpia el búfer

    mvwprintw(screen_buffer, 0, 0, "SCORE: %d", score);
    mvwprintw(screen_buffer, 0, 35, "HIGHEST SCORE: %d", high_score);
    mvwprintw(screen_buffer, 0, 70, "LIVES: %d", 3);
    // Dibuja al jugador
    mvwprintw(screen_buffer, player_y, player_x, "%c", PLAYER_SYMBOL);

    // Dibuja los enemigos
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
           mvwprintw(screen_buffer, enemies[i].y, enemies[i].x, "%c", ENEMY_SYMBOL);
        }
    }

    // Dibuja los proyectiles
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].active) {
            mvwprintw(screen_buffer, projectiles[i].y, projectiles[i].x, "%c", PROJECTILE_SYMBOL);
        }
    }

    // Dibuja la puntuación


    // Refresca el búfer a la pantalla real
    wnoutrefresh(screen_buffer);
    doupdate();
}



