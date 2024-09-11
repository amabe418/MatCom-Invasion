#include "Bomb.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "juegoIntegradoV1.h"
#include "ScreenShows.h"
#include "SoundEffect.h"

// Inicializar power-ups (vidas o bombas)
void initPowerup()
{

    if (numPowerups < 1)
    {
        powerups[numPowerups].x = rand() % TOTAL_WIDTH + START_WINDOW;
        powerups[numPowerups].y = 0;
        powerups[numPowerups].speed = 0.15;
        powerups[numPowerups].active = 1;
        numPowerups++;
    }
}

// Nueva función para ajustar la posición de las bombas según el redimensionamiento de la pantalla
void adjust_bomb_positions() {
    for (int i = 0; i < numPowerups; i++) {
        if (enemies[i].active) {
            // Recalcular posiciones relativas aquí si es necesario
            powerups[i].x  = (powerups[i].x - old_START_WINDOW + START_WINDOW); // Ajusta la posición x
            powerups[i].y = (powerups[i].y - (old_lines/2) + (LINES/2)); // Ajusta la posición y
        }
    }
}



// Actualizar power-ups
void updatePowerups()
{
    for (int i = 0; i < numPowerups; i++)
    {
            powerups[i].y += powerups[i].speed;
            if (powerups[i].y > LINES - 3)
            {
                powerups[i].active = 0;
                if (powerups[i].x>= player_x+player_running && powerups[i].x<= player_x+player_running+8 )
                {
                    lives -= 2;
                    playBackgroundSound(4);
                    if (lives <= 0)
                    {
                        lives = 0;
                        end_screen();
                    }
                }
                numPowerups--;
            }
    }
}
