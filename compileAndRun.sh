#!/bin/bash

# Redimensionar la terminal a un tamaño predeterminado
# Filas: 25, Columnas: 80 (ajusta estos valores según sea necesario)
printf '\e[8;50;80t'


# Esperar un breve momento para asegurarse de que el redimensionamiento se aplique
sleep 0.1

# Compilación
gcc -o MatComInvasion  Enemy.c Player.c Projectile.c ScreenDesign.c ScreenShows.c global.c Records.c juegoIntegradoV1.c GameSymbols.c SoundEffect.c Bomb.c Life.c -lncurses
# Recordar que para compilarlo debugueando hay que agregar -g delante de -o, porque si se agrega
# despues da error pues despues de -o lo que se espera es el nombre del binario a compilar
# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    sudo cp -p MatComInvasion /usr/local/bin
    rm -rf MatComInvasion
    sudo cp -rf sound /usr/local/bin
    
    # La secuencia de escape \033[1;32 es para activar el color verde fuerte en la consola
    # La secuencia de escape \033[0m es para reestablecer el color por defecto

    echo -e "\033[1;32mCompilación exitosa\033[0m"
    # Ejecución del programa
else
    # La secuencia de escape \033[1;31 es para activar el color rojo fuerte en la consola

    echo -e "\033[1;31mError en la compilación.\033[0m"
fi
