#include "Life.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "juegoIntegradoV1.h"
#include "ScreenShows.h"
#include "SoundEffect.h"
// Inicializar power-ups (vidas o bombas)
void initLives()
{

    if (numLives < 1)
    {
        livesBomb[numLives].x = rand() % TOTAL_WIDTH + START_WINDOW;
        livesBomb[numLives].y = 0;
        livesBomb[numLives].speed = 0.05;
        livesBomb[numLives].active = 1;
        numLives++;
    }
}

// Nueva función para ajustar la posición de las bombas según el redimensionamiento de la pantalla
void adjust_Lives_positions() {
    for (int i = 0; i < numLives; i++) {
        if (livesBomb[i].active) {
            // Recalcular posiciones relativas aquí si es necesario
            livesBomb[i].x  = (livesBomb[i].x - old_START_WINDOW + START_WINDOW); // Ajusta la posición x
            livesBomb[i].y = (livesBomb[i].y - (old_lines/2) + (LINES/2)); // Ajusta la posición y
        }
    }
}


// Actualizar power-ups
void updateLives()
{
    for (int i = 0; i < numLives; i++)
    {
            livesBomb[i].y += livesBomb[i].speed;
            if (livesBomb[i].y > LINES - 3)
            {
                livesBomb[i].active = 0;
                if (livesBomb[i].x>= player_x+player_running && livesBomb[i].x<= player_x+player_running+8 )
                {
                    playBackgroundSound(5);
                    lives += 2;
                }
                numLives--;
            }
        }
    
}