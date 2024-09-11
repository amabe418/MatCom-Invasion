// game_symbols.c

#include "Player.h"
#include "Enemy.h"

// Definiciones de símbolos del jugador y del enemigo
const char *PLAYER_SYMBOL[PLAYER_HEIGHT] = {
    "     /\\   ",  // La barra invertida necesita doble escape si está dentro de una cadena
    "   _/##\\_ ",  // El símbolo `\` debe ser `\\`
    " /\\|####|/\\"  // Aquí también, `\` es `\\`
};

const char *ENEMY_SYMBOL[ENEMY_HEIGHT] = {
    "  ___  ",
    " /___\\ ",
    "  /|\\  "
};


#define LIFE_SYMBOL "^-^ "