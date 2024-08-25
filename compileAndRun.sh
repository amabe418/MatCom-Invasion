#!/bin/bash

# Redimensionar la terminal a un tamaño predeterminado
# Filas: 25, Columnas: 80 (ajusta estos valores según sea necesario)
printf '\e[8;25;80t'

# Esperar un breve momento para asegurarse de que el redimensionamiento se aplique
sleep 0.1

# Compilación
gcc -o myprogram  Enemy.c Player.c Projectile.c ScreenDesign.c ScreenShows.c global.c Records.c juegoIntegradoV1.c -lncurses
#Recordar que para compilarlo debugueando hay que agregar -g delante de -o, porque si se agrega
#despues da error pues despues de -o lo que se espera es el nombre del binario a compilar
# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "Compilación exitosa, ejecutando el programa..."
    # Ejecución del programa
    ./myprogram
else
    echo "Error en la compilación."
fi
