# MatCom-Invasion
 Proyecto de Sistema Operativo de 4to semestre de Ciencia de la Computacion de la Universidad de La Habana.
 # Objetivo
 Desarrollar un juego de estilo arcade en C, similar al clásico "Alien Invaders", donde el jugador
 controla una nave espacial para defender la Tierra de una invasión alienígena. Este proyecto tiene
 como objetivo principal poner en práctica conceptos fundamentales de la asignatura Sistema
 Operativo, como la programación orientada a eventos, la concurrencia, la gestión de la memoria y
 el diseño de estrategias de planificación. Además, se busca familiarizar al estudiante con el trabajo
 en consola mediante un entorno de desarrollo de una máquina virtual con sistema operativo Arch
 Linux.

 
# ToDo List
- Arreglar el metodo de caer proyectiles para que salgan en posiciones random
- hay que restringir el intervalo de las x , porque siempre empiezan siempre en y=0.
- Lograr que el jugador se mueva --hoy 9 julio ARREGLADO
- ~~lograr que los proyectiles se lancen. --hoy 9 julio ARREGLADO~~
- hacer que el proyecto corra con el comando dado
- aumentar el numero de proyectiles.
- cambiar la estetica de la consola

TAREAS DEL 9 DE JULIO
-aumetar la velocidad del proyectil
-aumentar la velocidad de la nave
- evitar que se dibuje una pantalla nueva cada vez que haya que actualizarla, no queremos el borra-dibuja que hay todo el tiempo.
-el programa debe instalar la biblioteca ncurses automaticamente y offline ANTES de correr el programa, debemos tener un script para automatizar eso 
- ver la idea de jugar por niveles
-guardar a los enemigos en una cola, para que sean una cantidad liminada de enemigos
-definir el rango de colsiion entre proyectil y enemigo, la x del proyectil debe estar en el rango de la x
-agregar vidas, para no perder a la primera 
-CONDICIONES PARA PERDER UNA VIDA:
    --- la nave colisiona con el enemigo, en ese caso, se elimina tambien el enemigo
    --- el enemigo toca pasa el limite de la pantalla
-IMPORTANTE: que al abrir el juego, se abra una consola grande(como se quiera)



#PARA HOY:
- SEPARAR POR MODULOS
