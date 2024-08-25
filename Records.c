#include "Records.h"
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

void save_score(int score) {
    FILE *file = fopen("score.txt", "w");
    if (file == NULL) {
        perror("Error abriendo el archivo de puntaje");
        return;
    }
    fprintf(file, "Puntaje: %d\n", score);
    fclose(file);
}

int load_high_score() {
    FILE *file = fopen("high_score.txt", "r");
    if (file == NULL) {
        return 0; // Si no existe el archivo, el récord es 0
    }
    int high_score;
    fscanf(file, "%d", &high_score);
    fclose(file);
    return high_score;
}

void save_high_score(int high_score) {
    FILE *file = fopen("high_score.txt", "w");
    if (file == NULL) {
        perror("Error abriendo el archivo de récord");
        return;
    }
    fprintf(file, "%d\n", high_score);
    fclose(file);
}