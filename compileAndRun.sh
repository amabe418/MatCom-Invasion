#!/bin/bash

# Compilación
gcc -o myprogram juegoIntegradoV1.c Enemy.c Player.c Projectile.c ScreenDesign.c global.c -lncurses

# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "Compilación exitosa, ejecutando el programa..."
    # Ejecución del programa
    ./myprogram
else
    echo "Error en la compilación."
fi
