#include <ncurses.h>

void init() {
    initscr();       // Inicializa la pantalla para usar ncurses
    cbreak();        // Deshabilita la entrada de línea para obtener la entrada del usuario inmediatamente
    noecho();        // Evita que se muestre la entrada del usuario en la pantalla
    keypad(stdscr, TRUE);  // Habilita el teclado para capturar teclas especiales como las flechas
    curs_set(FALSE); // Oculta el cursor
}

void cleanup() {
    endwin();        // Finaliza el modo ncurses y devuelve la pantalla a su estado normal
}

int main() {
    init();          // Inicializa ncurses y la configuración de la pantalla

    int ch;
    // Bucle principal del juego que captura las teclas presionadas
    while ((ch = getch()) != 'q') { // El juego se cierra al presionar 'q'
        switch (ch) {
            case KEY_UP:
                // Mover nave hacia arriba
                printf("ARRIBA");
                break;
            case KEY_DOWN:
                // Mover nave hacia abajo
                printf("abajo");
                break;
            case KEY_LEFT:
                // Mover nave hacia la izquierda
                printf("izquierda");
                break;
            case KEY_RIGHT:
                // Mover nave hacia la derecha
                printf("derecha");
                break;
            case ' ':
                // Disparar proyectil
                 printf("push");
                break;
        }
    }

    cleanup();       // Finaliza ncurses antes de salir del programa
    return 0;
}
