
---

**Informe del Proyecto de Juego MatcomInvasion**

**Descripción del Juego:**
Este proyecto es un juego arcade de estilo clásico en el que el jugador debe proteger al mundo de las medusas invasoras. Las medusas solo descienden a la tierra, y el jugador no debe dejar que lo toque ni que sobrepase el limite donde comienza la nave, pues en ambos casos perderia una vida por cada enemigo que lo logre. Adem'as las fuerzas enemigas est'an haciendo pruebas de artiller'ia y envian bombas rojas que tienen como unico objetivo destruir al jugador y no importan si descienden mas que 'el, si este logra destruirlas gana 100 de puntuaci'on, si en cambio esta llega a tocarlo le quita 2 de vida, El jugador comienza con 5 vidas, pero a cada rato un infiltrado en el bando enemigo le enviar'a refuerzos de vidas, en un paquete verde que si logra alcanzar obtendr'a 2 vidas. La mision del jugador es eliminar a la mayor cantidad de enemigos posibles y perder'a cuando haya agotado todas sus vidas.

**Características Principales:**
1. **Jugador:**
   - Controlado mediante las teclas de flecha para moverse hacia la izquierda o derecha.
   - El jugador dispara proyectiles con la barra espaciadora.
   - Comienza con 5 vidas.
   
2. **Enemigos:**
   - Los enemigos aparecen en pantalla en intervalos regulares.
   - Se mueven hacia el jugador, y su velocidad se controla mediante un contador.
   - El jugador debe disparar a los enemigos para eliminarlos.

3. **Proyectiles:**
   - El jugador dispara proyectiles con el objetivo de destruir a los enemigos.
   - Los proyectiles tienen un límite máximo (definido por `MAX_PROJECTILES`).

4. **Power-ups:**
   - Los power-ups aparecen aleatoriamente en el juego, brindando ventajas al jugador.
   - Se manejan con un sistema de actualización continua.

5. **Vidas:**
   - El jugador comienza con 5 vidas, y puede ganar más a través de power-ups o perdiéndolas cuando es golpeado por enemigos.

6. **Interfaz Gráfica:**
   - Implementada con la librería **ncurses**, lo que permite crear gráficos simples en la terminal.
   - Utiliza un sistema de detección de colisiones para manejar la interacción entre el jugador, proyectiles, enemigos y power-ups.

**Componentes Técnicos:**

1. **Control de Entrada:**
   - El jugador utiliza las teclas de flecha para moverse y la barra espaciadora para disparar.
   - El manejo de entrada se realiza en un hilo separado, permitiendo una respuesta rápida y fluida a las acciones del jugador.

2. **Colisiones:**
   - El juego detecta colisiones entre los proyectiles y los enemigos, así como entre el jugador y las bombas.

3. **Hilos (Pthreads):**
   - El bucle principal del juego se maneja en un hilo separado para garantizar que las animaciones, movimientos de enemigos, proyectiles y power-ups sean fluidos y no se vean interrumpidos por la entrada del usuario.
   - Cada acción (disparar, mover al jugador) también se maneja en un hilo separado para mejorar la capacidad de respuesta del juego.

4. **Pantalla y Redimensionamiento:**
   - El tamaño de la pantalla se adapta dinámicamente al redimensionar la ventana de terminal, recalculando las posiciones del jugador y los enemigos en función de las nuevas dimensiones.

5. **Sistema de Puntuación y Vidas:**
   - El jugador acumula puntos al eliminar enemigos.
   - La puntuación más alta se guarda entre sesiones de juego, cargándose al inicio del juego.

---

### Enemigos

**1. Aparición de Enemigos:**
Los enemigos aparecen en posiciones predefinidas que se distribuyen a lo largo de la pantalla horizontalmente. Estas posiciones se calculan usando un sistema de reemplazo basado en el algoritmo de reloj (Clock Replacement Algorithm), el cual asegura que las posiciones no se reutilicen demasiado pronto.

- **Algoritmo de Posición de Aparición:**
  - Se utiliza un arreglo `position_state` para seguir el estado de cada posición de aparición.
    - **0**: No utilizada.
    - **1**: Utilizada.
  - Un puntero (`clock_hand`) avanza circularmente en el arreglo para determinar cuál será la próxima posición disponible.
  - Si una posición ya fue utilizada, el algoritmo continúa buscando hasta encontrar una posición no utilizada.

- **Posiciones Iniciales:**
  Las posiciones iniciales de aparición de los enemigos se calculan una vez al inicio del juego con base en un valor aleatorio y una distancia fija entre ellas. El primer valor es aleatorio, y los siguientes se incrementan por una constante.

**2. Movimiento de los Enemigos:**
Los enemigos se mueven verticalmente de arriba hacia abajo en la pantalla. El movimiento ocurre en intervalos de tiempo regulares, controlados por un contador y un umbral que determina la velocidad de movimiento de los enemigos.

- **Velocidad de Movimiento:**
  La velocidad con la que los enemigos descienden por la pantalla se ajusta sumando una pequeña cantidad a su posición en el eje y (`enemies[i].y += 0.4`). Esto crea un efecto de movimiento suave y controlado.

- **Ajuste por Redimensionamiento de Pantalla:**
~~  Si el tamaño de la terminal cambia durante el juego, la posición de los enemigos también se ajusta proporcionalmente al nuevo tamaño de la pantalla, asegurando que su ubicación relativa no se vea afectada.~~

**3. Colisiones y Finalización:**
Cuando un enemigo alcanza la parte inferior de la pantalla sin ser destruido, este desaparece y reduce las vidas del jugador. Si las vidas llegan a cero, el juego termina.

- **Sistema de Colisiones:**
  - Los enemigos se desactivan cuando llegan al borde inferior de la pantalla donde termina la figura del jugador (`enemies[i].y >= LINES - ENEMY_WIDTH + 1`).
  - Cuando un enemigo alcanza el borde, el jugador pierde una vida.
  - Si las vidas llegan a cero, se activa la pantalla de fin de juego.

**4. Implementación Técnica:**
- **Función `spawn_enemy`:** 
  Esta función busca un enemigo inactivo en el arreglo `enemies[]` y le asigna una posición aleatoria de aparición usando el algoritmo de reemplazo de reloj, que escoge una posicion de 10 posibles posiciones que pueden tener los enemigos para asi evitar en gran parte solapamientos de enemigos. Estas posiciones ademas estan en un rango de la pantalla para evitar largos desplazamientos del jugador.
  
- **Función `move_enemies`:** 
  Los enemigos activos descienden por la pantalla y son desactivados si llegan al límite inferior, momento en el cual también se reduce el número de vidas del jugador.

---

### Jugador

**1. Control del Jugador:**
El jugador puede moverse horizontalmente por la pantalla. El control se gestiona mediante hilos (threads) que permiten al jugador moverse fluidamente de izquierda a derecha, evitando interrupciones en otros procesos del juego, como la aparición de enemigos o las colisiones.

- **Interacción con el Teclado:**
  La posición del jugador se ajusta en respuesta a la entrada del teclado, específicamente a las teclas de flecha izquierda (`KEY_LEFT`) y flecha derecha (`KEY_RIGHT`). Esta interacción se maneja dentro de la función `move_player`, que se ejecuta en un hilo separado para mejorar la fluidez del juego.

- **Movimiento Restringido:**
  El jugador tiene límites de movimiento horizontales definidos:
  - No puede moverse más allá del borde izquierdo de la pantalla (`START_WINDOW`).
  - Tampoco puede superar el límite derecho de la pantalla (`HORIZONTAL_END_WINDOW`).

**2. Movimiento y Dibujo del Jugador:**
El jugador se representa visualmente en la pantalla mediante un conjunto de caracteres (`PLAYER_SYMBOL[]`), que forman una figura definida.

- **Borrado de la Posición Anterior:**
  Antes de actualizar la posición del jugador, el juego borra la figura anterior del jugador en su ubicación actual para evitar superposición de gráficos. Esto se hace con la función `mvwprintw` que reemplaza el área anterior con espacios en blanco (`"        "`).

- **Actualización de Posición:**
  Dependiendo de la dirección del movimiento, el juego ajusta la variable `player_running`, que controla el desplazamiento del jugador en el eje horizontal. 
  - Si el jugador se mueve hacia la izquierda y no ha alcanzado el límite izquierdo, la posición en `player_running` disminuye.
  - Si se mueve hacia la derecha y no ha alcanzado el borde derecho, la posición aumenta.

- **Dibujo del Jugador en la Nueva Posición:**
  Después de actualizar la posición, la figura del jugador se vuelve a dibujar en su nueva ubicación. Para darle un efecto visual destacado, se aplica un color y negrita (`COLOR_PAIR(2) | A_BOLD`).

**3. Sincronización y Seguridad de los Hilos:**
Dado que el movimiento del jugador puede interactuar con otras partes del juego, como la aparición de enemigos o los disparos del jugador, se utilizan mecanismos de sincronización, como un mutex (`game_mutex`), para evitar condiciones de carrera entre hilos.

- **Mutex:**
  - El `pthread_mutex_lock` asegura que solo un hilo a la vez puede modificar la posición del jugador, lo que evita inconsistencias gráficas o errores en la lógica del juego.
  - Después de actualizar la posición y dibujar al jugador, se libera el mutex con `pthread_mutex_unlock`.

**4. Implementación Técnica:**
- **Función `move_player`:** 
  La función maneja el movimiento del jugador. Recibe como argumento la dirección en la que se debe mover (izquierda o derecha). Dentro de la función, se actualiza la posición del jugador, se borra la figura anterior y se vuelve a dibujar en la nueva posición.

---

Esta sección cubre el funcionamiento del jugador dentro del juego, detallando cómo se gestiona su movimiento, sincronización y representación visual. ¿Hay algún aspecto adicional del jugador o del juego que te gustaría ampliar?

Aquí tienes una sección detallada enfocada en el comportamiento de las bombas en el juego, siguiendo el formato anterior:

---

### Bombas

**1. Aparición y Control de las Bombas:**
En el juego, las bombas (definidas como power-ups con efectos negativos) aparecen en la pantalla de manera aleatoria y caen desde la parte superior. La función principal que gestiona la aparición y actualización de estas bombas es crucial para agregar dificultad al juego.

- **Condiciones de Aparición:**
  La función `initPowerup()` se encarga de inicializar los power-ups, que incluyen bombas. Las bombas aparecen bajo dos condiciones:
  1. El número total de power-ups activos (`numPowerups`) debe ser menor a 1.
  2. Se genera un valor aleatorio con `rand()`, y si el resultado es mayor que `START_WINDOW`, se crea una nueva bomba.
  
- **Posición Inicial:**
  - Las bombas aparecen en una posición horizontal aleatoria dentro de los límites de la pantalla (`HORIZONTAL_END_WINDOW`).
  - Inicialmente, la posición vertical (`y`) de la bomba es 0, lo que significa que aparece en la parte superior de la pantalla.

- **Velocidad:**
  La velocidad de caída de la bomba se establece en `0.15`, lo que controla la rapidez con la que descienden las bombas por la pantalla.

**2. Movimiento de las Bombas:**
  La función `updatePowerups()` se encarga de mover las bombas hacia abajo de la pantalla conforme avanza el juego. Cada bomba activa se mueve incrementando su posición vertical (`y`) en cada actualización, siguiendo su velocidad predefinida.

- **Desplazamiento Vertical:**
  Cada actualización de la pantalla aumenta la posición `y` de la bomba en función de su velocidad, haciendo que esta descienda progresivamente desde la parte superior hasta el fondo de la pantalla.

**3. Colisión y Efectos de las Bombas:**
- **Impacto con el Jugador:**
  Si una bomba cae dentro del rango de acción del jugador, definida por la distancia horizontal entre la bomba y el jugador (`abs(powerups[i].x - (player_x + player_running)) <= RANGO`), ocurre una colisión que reduce la cantidad de vidas del jugador.
  - Cada colisión con una bomba reduce las vidas del jugador en 2 (`lives -= 2`).
  - Si las vidas del jugador caen a 0 o menos, se activa la pantalla de fin de juego con la función `end_screen()`.

**4. Eliminación de Bombas fuera de la Pantalla:**
Cuando una bomba alcanza el fondo de la pantalla sin impactar al jugador, debe ser eliminada para evitar que se sigan procesando objetos innecesarios.

- **Reutilización de Espacio en el Array:**
  - Si una bomba llega al borde inferior de la pantalla (`powerups[i].y > LINES - 3`), se elimina y los elementos restantes en el array `powerups[]` se desplazan hacia adelante para llenar el espacio vacío.
  - Esto se hace en un bucle que recorre los elementos desde la posición actual de la bomba eliminada (`i`) hasta el último elemento activo en el array, asegurando que no haya huecos en la lista de power-ups activos.
  - Una vez que la bomba se elimina, el contador `numPowerups` se reduce en 1 para reflejar el número correcto de power-ups activos.

**5. Sincronización de Bombas:**
Dado que el juego puede tener múltiples power-ups y bombas activos en simultáneo, la actualización de sus posiciones y efectos se gestiona en tiempo real a través de la función `updatePowerups()`. Esta función asegura que las bombas se muevan de manera sincronizada con el resto del juego, generando una mayor dificultad para el jugador.

**6. Implementación Técnica:**
- **Función `initPowerup`:**
  Esta función verifica si es posible agregar un nuevo power-up (bomba) y, de ser así, inicializa la posición y velocidad del nuevo objeto.

- **Función `updatePowerups`:**
  Actualiza la posición vertical de cada bomba activa. Si una bomba cae al suelo o colisiona con el jugador, se procesa el efecto correspondiente, como la pérdida de vidas o la eliminación de la bomba.

---

Esta sección explica el manejo de las bombas, su aparición, movimiento, y colisión con el jugador, lo cual aumenta el desafío dentro del juego. ¿Hay algún otro detalle que te gustaría agregar o cambiar respecto a las bombas o el juego en general?

Aquí tienes una explicación detallada enfocada en el comportamiento de las **vidas** en el juego, siguiendo el formato de los otros elementos:

---

### Vidas

**1. Aparición y Control de las Vidas:**
Las vidas, implementadas como power-ups que aumentan el número de vidas del jugador, aparecen de manera aleatoria en la pantalla y caen desde la parte superior, similares a las bombas. El propósito de estos power-ups es proporcionar una manera de recuperar vidas durante el juego.

- **Condiciones de Aparición:**
  La función `initLives()` es responsable de la inicialización de las vidas (power-ups positivos). Las vidas aparecen en las siguientes condiciones:
  1. El número total de power-ups de vida activos (`numLives`) debe ser menor a 1.
  2. Se genera un valor aleatorio con `rand()`, y si el resultado es mayor que `START_WINDOW`, se crea una nueva vida.

- **Posición Inicial:**
  - La posición horizontal de aparición de las vidas es aleatoria dentro del rango de la pantalla de juego (`HORIZONTAL_END_WINDOW`).
  - La posición vertical inicial (`y`) de la vida es `0`, lo que significa que aparece en la parte superior de la pantalla.

- **Velocidad:**
  La velocidad de caída de las vidas es menor que la de las bombas, establecida en `0.05`, lo que le da al jugador más tiempo para recogerlas mientras caen.

**2. Movimiento de las Vidas:**
  La función `updateLives()` se encarga de mover las vidas hacia abajo en la pantalla. Cada vida activa se mueve hacia abajo incrementando su posición vertical (`y`) con cada actualización, siguiendo su velocidad predeterminada.

- **Desplazamiento Vertical:**
  Cada actualización de la pantalla incrementa la posición `y` de cada vida en función de su velocidad, lo que hace que caigan desde la parte superior de la pantalla hacia el fondo, a un ritmo más lento que las bombas.

**3. Colisión y Efectos de las Vidas:**
- **Interacción con el Jugador:**
  Si una vida cae dentro del rango de acción del jugador (definido por la distancia horizontal entre la vida y el jugador, `abs(livesBomb[i].x - (player_x + player_running)) <= RANGO`), el jugador obtiene una recompensa de **2 vidas adicionales**.
  - Cada vida recogida aumenta el valor de `lives` en 2 (`lives += 2`).
  - Esto ayuda al jugador a recuperar vidas perdidas durante el juego, permitiéndole continuar jugando por más tiempo.

**4. Eliminación de Vidas fuera de la Pantalla:**
Cuando una vida llega al borde inferior de la pantalla sin ser recogida por el jugador, se elimina para evitar el procesamiento de elementos inactivos.

- **Reutilización de Espacio en el Array:**
  - Si una vida alcanza el borde inferior de la pantalla (`livesBomb[i].y > LINES - 3`) sin ser recogida, se elimina y los elementos restantes en el array `livesBomb[]` se desplazan hacia adelante para llenar el hueco que dejó.
  - El bucle que gestiona esto recorre los elementos desde la posición de la vida eliminada (`i`) hasta el último elemento activo del array, asegurándose de que no haya huecos en la lista de power-ups de vida activos.
  - Después de eliminar la vida, se reduce el contador `numLives` en 1 para reflejar el número correcto de power-ups de vida activos.

**5. Sincronización de las Vidas:**
Al igual que las bombas, las vidas deben moverse y actualizarse de manera sincronizada con el resto de los objetos en el juego. La función `updateLives()` asegura que las vidas caigan de forma continua y sin interrupciones, manteniendo la dinámica del juego.

**6. Implementación Técnica:**
- **Función `initLives`:**
  Verifica si es posible generar una nueva vida. Si se cumplen las condiciones, inicializa la posición y la velocidad del power-up de vida, y lo marca como activo.

- **Función `updateLives`:**
  Actualiza la posición vertical de cada vida activa, las elimina si alcanzan el borde inferior de la pantalla, y aumenta las vidas del jugador si hay una colisión.

---

Esta sección explica la mecánica de las vidas como power-ups positivos, su aparición, movimiento, y cómo interactúan con el jugador para aumentar el número de vidas. Esto agrega un componente estratégico para que el jugador recupere recursos en medio del juego. 

¿Te gustaría ajustar algún aspecto de la lógica o agregar más detalles?

Aquí tienes la descripción para la implementación de los **proyectiles** en el juego, incluyendo su disparo, movimiento, y detección de colisiones:

---

### Proyectiles

**1. Disparo de Proyectiles:**
Los proyectiles son disparados por el jugador hacia los enemigos o power-ups. Esta funcionalidad está controlada por la función `shoot_projectile`, la cual gestiona la creación y activación de los proyectiles.

- **Condiciones de Disparo:**
  - Cada vez que el jugador dispara, se busca el primer proyectil inactivo en el array `projectiles[]` y se activa.
  - La posición inicial del proyectil es justo encima del jugador, centrada horizontalmente en relación a la posición actual del jugador (`player_x + player_running + PLAYER_WIDTH / 2 + 1`) y una fila arriba de la posición del jugador (`player_y - 1`).
  - Una vez activado, se dibuja el proyectil en la pantalla usando `addstr(PROJECTILE_SYMBOL)` para mostrar su símbolo.

- **Sonido de Disparo:**
  Se reproduce un efecto de sonido cada vez que se dispara un proyectil, utilizando la función `playBackgroundSound(3)`.

**2. Movimiento de los Proyectiles:**
La función `move_projectiles` se encarga de mover los proyectiles activos hacia arriba en la pantalla con cada actualización.

- **Movimiento Vertical:**
  Cada proyectil activo se mueve hacia arriba decrementando su posición `y` (`projectiles[i].y = projectiles[i].y - 1`). Este movimiento continuo hace que el proyectil avance hacia los enemigos desde la parte inferior de la pantalla.
  
- **Desactivación al Salir de Pantalla:**
  Si un proyectil alcanza la parte superior de la pantalla (`y < 0`), se desactiva (`projectiles[i].active = 0`), ya que ha salido de la zona visible de juego.

**3. Detección de Colisiones:**
La función `detect_collisions` se encarga de verificar si algún proyectil activo colisiona con enemigos o power-ups, gestionando las interacciones de los proyectiles en el juego.

- **Colisiones con Enemigos:**
  - Cada proyectil activo se compara con todos los enemigos activos.
  - Si un proyectil está lo suficientemente cerca de un enemigo (basado en una distancia horizontal dentro del `RANGO` y una distancia vertical de 1), se considera una colisión.
  - Tras la colisión, el proyectil y el enemigo se desactivan (`projectiles[i].active = 0`, `enemies[j].active = 0`), y se reproduce un efecto de sonido (`playBackgroundSound(2)`).
  - Además, se incrementa la puntuación del jugador en 1 punto (`score++`).

- **Colisiones con Power-Ups:**
  - También se verifica si un proyectil colisiona con algún power-up (bombas o vidas).
  - Si un proyectil está cerca de un power-up (tanto horizontalmente como verticalmente, dentro del rango de colisión), el power-up es destruido y se otorgan 100 puntos al jugador (`score += 100`), desactivando el power-up (`powerups[j].active = 0`).

**4. Sincronización y Bloqueo de Recursos:**
- **Uso de Mutex:**
  Para evitar problemas de concurrencia, tanto la función de disparo (`shoot_projectile`) como la de detección de colisiones (`detect_collisions`) están protegidas por un mutex (`pthread_mutex_lock(&game_mutex)` y `pthread_mutex_unlock(&game_mutex)`), garantizando que las operaciones críticas relacionadas con los proyectiles no sean interrumpidas por otros hilos.

**5. Implementación Técnica:**

- **Función `shoot_projectile`:**
  Dispara un proyectil desde la posición actual del jugador, lo activa y lo dibuja en la pantalla.

- **Función `move_projectiles`:**
  Mueve los proyectiles activos hacia arriba en la pantalla y desactiva aquellos que salen de los límites.

- **Función `detect_collisions`:**
  Detecta colisiones entre proyectiles y enemigos o power-ups. En caso de colisión, se desactiva el proyectil, se elimina el enemigo o power-up, y se otorgan puntos al jugador.

---

Este sistema asegura que los proyectiles se manejen de manera eficiente, sincronizando el disparo, movimiento y detección de colisiones con el entorno del juego. Esto permite al jugador interactuar activamente disparando contra enemigos y power-ups mientras juega. 

¿Te gustaría ajustar algún aspecto de la lógica de los proyectiles o agregar más funcionalidades?

Aquí tienes la descripción del diseño de pantalla, detallando cómo se dibujan los diferentes elementos del juego usando `ncurses`, incluyendo el jugador, los enemigos, los proyectiles, las bombas y las vidas, además del puntaje y las vidas restantes.

---

### Diseño de Pantalla

El diseño de pantalla se basa en una ventana creada con `ncurses` que actúa como un buffer para actualizar todos los elementos visuales del juego en un solo paso, optimizando el rendimiento visual. La estructura está organizada de forma que todos los elementos del juego se dibujan en una ventana de buffer y luego se muestran al usuario.

---

**1. Inicialización de la Pantalla**

- **Función `init_screen_buffer`**:
  - Se crea un buffer de pantalla llamado `screen_buffer` usando la función `newwin` de `ncurses`.
  - Los parámetros de `newwin` definen el tamaño de la ventana: `GAME_HEIGHT` por `TERMINAL_WIDTH`, y la posición inicial de la ventana (`GAME_START_Y`, `GAME_START_X`).

---

**2. Actualización de Pantalla**

La función `update_screen` actualiza todos los elementos de la pantalla dentro del buffer, y luego refleja los cambios en la pantalla real.

- **Uso de Colores**:
  - Los colores se activan con `start_color` y se definen varios pares de colores (texto, fondo) usando `init_pair`.
    - **Pares de colores**:
      - `COLOR_PAIR(1)` para las bombas (rojo).
      - `COLOR_PAIR(2)` para el jugador (amarillo).
      - `COLOR_PAIR(3)` para la interfaz (cian).
      - `COLOR_PAIR(4)` para los enemigos (blanco).
      - `COLOR_PAIR(5)` para las vidas (verde).
  
- **Limpieza del Buffer**:
  - Se usa `werase(screen_buffer)` para limpiar el contenido actual del buffer antes de redibujar los elementos.

---

**3. Elementos Visuales del Juego**

Cada elemento visual en el juego se dibuja por separado dentro del buffer utilizando `mvwprintw` para colocar texto en posiciones específicas.

- **Interfaz del Jugador (Puntaje y Vidas)**:
  - Se dibuja el puntaje del jugador, el puntaje más alto y las vidas restantes en la parte superior de la pantalla usando el par de colores `COLOR_PAIR(3)` y `A_BOLD` (negrita).
  - Ejemplo: 
    - `SCORE: %d` para mostrar el puntaje actual.
    - `HIGHEST SCORE: %d` para el puntaje más alto.
    - `LIVES: %d` para mostrar las vidas restantes.

- **Dibujo del Jugador**:
  - El jugador se dibuja en su posición actual con el símbolo definido por `PLAYER_SYMBOL[]` y usando el par de colores `COLOR_PAIR(2)` para resaltarlo en amarillo con negrita.

- **Dibujo de los Enemigos**:
  - Se dibujan todos los enemigos activos en sus posiciones respectivas. Cada enemigo usa el símbolo definido por `ENEMY_SYMBOL[]` y se resalta en blanco (`COLOR_PAIR(4)`).
  - Si un enemigo no está activo, no se dibuja.

- **Dibujo de los Proyectiles**:
  - Todos los proyectiles activos se dibujan en sus respectivas posiciones con el símbolo `PROJECTILE_SYMBOL`. 
  - No hay color específico asignado para los proyectiles, se dibujan con los valores predeterminados.

- **Dibujo de las Bombas**:
  - Las bombas (power-ups) se dibujan en rojo utilizando `COLOR_PAIR(1)`. 
  - Las bombas activas se dibujan en su posición actual con el símbolo `BOMB_SYMBOL`.

- **Dibujo de las Vidas**:
  - Las vidas adicionales que aparecen como power-ups se dibujan en verde usando `COLOR_PAIR(5)`.
  - Se usan las posiciones correspondientes de `livesBomb[]` para dibujarlas, usando el símbolo `LIFE_SYMBOL`.

---

**4. Refresco de la Pantalla**

Después de dibujar todos los elementos en el buffer de pantalla:

- Se usa `wnoutrefresh(screen_buffer)` para marcar el buffer para refrescar.
- Luego, `doupdate()` realiza la actualización real de la pantalla, mostrando todos los cambios de una sola vez para evitar parpadeos y mejorar el rendimiento gráfico.

---

Este diseño de pantalla asegura que todos los elementos se dibujen y actualicen en la pantalla de manera eficiente, proporcionando una interfaz de juego fluida con diferentes colores y efectos visuales.

¿Te gustaría realizar algún ajuste o añadir más detalles a este diseño de pantalla?


En el proyecto del juego arcade, se utilizan varias pantallas temporales para guiar al jugador a través de diferentes estados del juego, como la pantalla de inicio, la pantalla de pausa y la pantalla de finalización del juego. Estas pantallas se muestran usando la biblioteca `ncurses`, que permite gestionar interfaces de texto en la terminal de una manera flexible.

A continuación se describe el proceso de cómo se implementan y muestran las pantallas temporales en el código proporcionado:

### Pantalla de Inicio (`start_screen`)

1. **Inicialización de `ncurses`:**
   La función `start_screen` inicializa el entorno de `ncurses` llamando a funciones como `initscr()`, `cbreak()`, `noecho()`, y `keypad(stdscr, TRUE)` para configurar el manejo de entradas y salidas en la terminal.
   
2. **Definición de Colores:**
   Se utilizan colores personalizados mediante la función `start_color()` y `init_pair()` para mejorar la visualización del menú.

3. **Interfaz de Menú:**
   - Se muestra un menú básico que tiene dos opciones: **JUGAR** y **SALIR**.
   - El jugador puede moverse entre las opciones usando las teclas de flecha y seleccionar una opción con la tecla **Enter**.
   - Las opciones se resaltan usando colores y atributos de `ncurses` como `A_BOLD`.

4. **Acciones:**
   - Si el jugador selecciona **JUGAR**, la pantalla se limpia y el juego comienza.
   - Si selecciona **SALIR**, se guarda el puntaje actual, se verifica si es un nuevo récord, se limpia la pantalla, y el programa termina.


### Pantalla de Fin de Juego (`end_screen`)

1. **Finalización del Juego:**
   Cuando el jugador pierde todas sus vidas, se muestra una pantalla de **JUEGO TERMINADO**.
   
2. **Interfaz de Opciones:**
   Al igual que en las pantallas anteriores, el jugador puede elegir entre **REINICIAR** el juego o **SALIR**.
   - **REINICIAR** vuelve a comenzar el juego desde cero.
   - **SALIR** guarda el puntaje, actualiza el récord, limpia la pantalla, y finaliza el juego.

### Sincronización y Bloqueo de Entrada

En todas estas funciones, se utiliza un mutex (`pthread_mutex_lock()`) para evitar que las entradas del jugador interfieran con otras partes del juego mientras se muestran estas pantallas temporales. Esto asegura que el manejo de entradas y el flujo del juego estén controlados de manera sincronizada.

### Limpieza y Finalización de `ncurses`

Al final de cada función de pantalla temporal (inicio, pausa, fin de juego), se llama a la función `endwin()` para restaurar el estado normal de la terminal una vez que se sale de `ncurses`, evitando que el terminal quede en un estado de visualización incorrecto al salir del juego.

---

Estas pantallas son fundamentales para proporcionar una experiencia de usuario interactiva en el juego, permitiendo al jugador navegar por los diferentes estados del juego de manera clara y consistente.


El código que implementa los efectos de sonido en el proyecto de juego arcade utiliza procesos hijos para reproducir archivos de sonido en diferentes situaciones del juego, como la música de fondo, explosiones, y disparos. Para gestionar estos sonidos, se usan llamadas a sistema como `fork()`, `execlp()`, y `kill()` en combinación con el reproductor de audio `aplay` para manejar archivos `.mp3` y `.wav`.

### Descripción del proceso de reproducción de efectos de sonido:

1. **Definición de variables:**
   Se definen tres variables globales de tipo `pid_t` (ID de proceso) para almacenar los PIDs (Process IDs) de los procesos que se encargarán de reproducir los sonidos:
   - `BackgroundSoundPID`: Almacena el PID del proceso que reproduce la música de fondo.
   - `ExplosionSoundPID`: Almacena el PID del proceso que reproduce el sonido de explosiones.
   - `ShootSoundPID`: Almacena el PID del proceso que reproduce el sonido de disparos.

2. **Selección de archivos de sonido:**
   Cada efecto de sonido está asociado con un archivo específico:
   - `BackGroundFileName`: Archivo de música de fondo.
   - `ExplosionFileName`: Archivo de sonido de explosión.
   - `ShootFileName`: Archivo de sonido de disparo.

3. **Función `playBackgroundSound(int soundType)`:**
   Esta función se encarga de reproducir diferentes efectos de sonido dependiendo del valor del parámetro `soundType`.
   - El parámetro `soundType` determina qué tipo de sonido se va a reproducir:
     - `1` para la música de fondo.
     - `2` para el sonido de explosiones.
     - `3` para el sonido de disparos.
   
   El flujo de la función es el siguiente:
   - Se selecciona el archivo de sonido adecuado y se almacena en la variable `filename`, mientras que el PID del proceso hijo correspondiente se almacena en `soundPID`.
   - La función verifica si el archivo de sonido existe y es accesible usando `access()`. Si no lo es, la función retorna sin hacer nada.
   - Se crea un proceso hijo mediante `fork()`. Si `fork()` retorna `0`, significa que estamos en el proceso hijo. Este proceso hijo se encargará de ejecutar `aplay` para reproducir el archivo de sonido, redirigiendo la salida estándar y de error a `/dev/null` para evitar cualquier mensaje en la consola.
   - En el proceso padre, se guarda el PID del proceso hijo que reproduce el sonido en la variable correspondiente (`BackgroundSoundPID`, `ExplosionSoundPID`, o `ShootSoundPID`).

4. **Función `stop_sound(pid_t pid)`:**
   Esta función se utiliza para detener un sonido en ejecución. Recibe como parámetro el PID del proceso que está reproduciendo el sonido y envía una señal `SIGKILL` a ese proceso, terminando su ejecución.

   En el código actual, la función siempre envía la señal de terminación al proceso que reproduce la música de fondo (`BackgroundSoundPID`), aunque podría adaptarse para detener otros tipos de sonidos.

### Resumen del funcionamiento:
- El sistema de sonido del juego está basado en la creación de procesos hijos que reproducen los archivos de sonido utilizando la herramienta `aplay`. 
- Cada vez que un evento del juego, como disparar o una explosión, ocurre, se lanza un proceso que reproduce el archivo de sonido correspondiente.
- Para evitar interferencias en la jugabilidad, la salida de estos procesos se redirige a `/dev/null` para evitar cualquier mensaje en la consola.
- Los sonidos se pueden detener enviando una señal `SIGKILL` al proceso que los reproduce, lo cual finaliza inmediatamente el proceso de sonido.
Aquí está la explicación detallada del proceso de guardar y cargar el puntaje máximo en el juego:

### Proceso de Guardar el Puntaje Máximo

1. **Guardar el Puntaje Actual:**
   La función `save_score(int score)` guarda el puntaje actual del juego en un archivo llamado `score.txt`. Aquí está cómo funciona:
   - Se abre el archivo `score.txt` en modo de escritura (`"w"`). Si el archivo no se puede abrir, se imprime un mensaje de error.
   - Se escribe el puntaje actual en el archivo en el formato `"Puntaje: %d\n"`.
   - Finalmente, se cierra el archivo.

2. **Cargar el Puntaje Máximo:**
   La función `load_high_score()` carga el puntaje más alto guardado desde un archivo llamado `high_score.txt`. El proceso es el siguiente:
   - Se abre el archivo `high_score.txt` en modo de lectura (`"r"`). Si el archivo no existe, se asume que el récord es 0.
   - Se lee el puntaje máximo almacenado en el archivo.
   - Se cierra el archivo y se retorna el puntaje máximo.

3. **Guardar el Puntaje Máximo:**
   La función `save_high_score(int high_score)` guarda el puntaje máximo en el archivo `high_score.txt`. Aquí está el procedimiento:
   - Se abre el archivo `high_score.txt` en modo de escritura (`"w"`). Si el archivo no se puede abrir, se imprime un mensaje de error.
   - Se escribe el puntaje máximo en el archivo en el formato `"%d\n"`.
   - Finalmente, se cierra el archivo.

### Resumen del Código

- **`save_score(int score)`**: Guarda el puntaje actual en `score.txt`.
- **`load_high_score()`**: Lee el puntaje más alto guardado de `high_score.txt`. Si el archivo no existe, retorna 0.
- **`save_high_score(int high_score)`**: Guarda el puntaje más alto en `high_score.txt`.

Este sistema permite que el juego mantenga un registro del puntaje máximo alcanzado a lo largo de diferentes sesiones de juego, proporcionando una forma de comparar el rendimiento actual con el mejor desempeño histórico.


Aquí está la explicación detallada del proceso para manejar los símbolos del jugador y los enemigos en el juego:

### Proceso de Manejo de Símbolos en el Juego

1. **Símbolos del Jugador:**
   En el archivo `game_symbols.c`, se definen los símbolos que representan al jugador en el juego. Estos símbolos están almacenados en un arreglo de cadenas de caracteres (`const char *PLAYER_SYMBOL[PLAYER_HEIGHT]`), donde cada cadena representa una línea del símbolo del jugador.

   - **Definición del Símbolo del Jugador:**
     ```c
     const char *PLAYER_SYMBOL[PLAYER_HEIGHT] = {
         "     /\\   ",  // La barra invertida necesita doble escape si está dentro de una cadena
         "   _/##\\_ ",  // El símbolo `\` debe ser `\\`
         " /\\|####|/\\"
     };
     ```
     - El símbolo del jugador se define como una serie de cadenas que juntas forman una representación gráfica del jugador. La barra invertida (`\`) debe ser escapada como `\\` en cadenas de caracteres en C para evitar errores de interpretación.
     - `PLAYER_HEIGHT` es una constante que define el número de líneas en la representación gráfica del jugador.

2. **Símbolos del Enemigo:**
   Similarmente, los símbolos que representan a los enemigos se definen en un arreglo de cadenas de caracteres (`const char *ENEMY_SYMBOL[ENEMY_HEIGHT]`).

   - **Definición del Símbolo del Enemigo:**
     ```c
     const char *ENEMY_SYMBOL[ENEMY_HEIGHT] = {
         "  ___  ",
         " /___\\ ",
         "  /|\\  "
     };
     ```
     - El símbolo del enemigo se define como un arreglo de cadenas que juntas forman la representación gráfica del enemigo. Aquí también se utilizan secuencias de escape para representar correctamente los caracteres especiales.
     - `ENEMY_HEIGHT` es una constante que define el número de líneas en la representación gráfica del enemigo.

3. **Símbolo de Vida:**
   Se define un símbolo simple para representar las vidas restantes del jugador, almacenado en una cadena de caracteres.

   - **Definición del Símbolo de Vida:**
     ```c
     #define LIFE_SYMBOL "^-^ "
     ```
     - `LIFE_SYMBOL` es una constante que contiene el símbolo que se usará para representar la vida del jugador en la interfaz del juego.

### Resumen del Código

- **`PLAYER_SYMBOL`**: Define el símbolo gráfico del jugador, compuesto por varias líneas de texto.
- **`ENEMY_SYMBOL`**: Define el símbolo gráfico del enemigo, también compuesto por varias líneas de texto.
- **`LIFE_SYMBOL`**: Define un símbolo para representar la vida restante del jugador.

Estos símbolos se utilizan para renderizar gráficamente al jugador y a los enemigos en la pantalla del juego, creando una representación visual que facilita la interacción del jugador con el juego.

Aquí está la explicación detallada del proceso para manejar los símbolos del jugador y los enemigos en el juego:

### Proceso de Manejo de Símbolos en el Juego

1. **Símbolos del Jugador:**
   En el archivo `game_symbols.c`, se definen los símbolos que representan al jugador en el juego. Estos símbolos están almacenados en un arreglo de cadenas de caracteres (`const char *PLAYER_SYMBOL[PLAYER_HEIGHT]`), donde cada cadena representa una línea del símbolo del jugador.

   - **Definición del Símbolo del Jugador:**
     ```c
     const char *PLAYER_SYMBOL[PLAYER_HEIGHT] = {
         "     /\\   ",  // La barra invertida necesita doble escape si está dentro de una cadena
         "   _/##\\_ ",  // El símbolo `\` debe ser `\\`
         " /\\|####|/\\"
     };
     ```
     - El símbolo del jugador se define como una serie de cadenas que juntas forman una representación gráfica del jugador. La barra invertida (`\`) debe ser escapada como `\\` en cadenas de caracteres en C para evitar errores de interpretación.
     - `PLAYER_HEIGHT` es una constante que define el número de líneas en la representación gráfica del jugador.

2. **Símbolos del Enemigo:**
   Similarmente, los símbolos que representan a los enemigos se definen en un arreglo de cadenas de caracteres (`const char *ENEMY_SYMBOL[ENEMY_HEIGHT]`).

   - **Definición del Símbolo del Enemigo:**
     ```c
     const char *ENEMY_SYMBOL[ENEMY_HEIGHT] = {
         "  ___  ",
         " /___\\ ",
         "  /|\\  "
     };
     ```
     - El símbolo del enemigo se define como un arreglo de cadenas que juntas forman la representación gráfica del enemigo. Aquí también se utilizan secuencias de escape para representar correctamente los caracteres especiales.
     - `ENEMY_HEIGHT` es una constante que define el número de líneas en la representación gráfica del enemigo.

3. **Símbolo de Vida:**
   Se define un símbolo simple para representar las vidas restantes del jugador, almacenado en una cadena de caracteres.

   - **Definición del Símbolo de Vida:**
     ```c
     #define LIFE_SYMBOL "^-^ "
     ```
     - `LIFE_SYMBOL` es una constante que contiene el símbolo que se usará para representar la vida del jugador en la interfaz del juego.

### Resumen del Código

- **`PLAYER_SYMBOL`**: Define el símbolo gráfico del jugador, compuesto por varias líneas de texto.
- **`ENEMY_SYMBOL`**: Define el símbolo gráfico del enemigo, también compuesto por varias líneas de texto.
- **`LIFE_SYMBOL`**: Define un símbolo para representar la vida restante del jugador.

Estos símbolos se utilizan para renderizar gráficamente al jugador y a los enemigos en la pantalla del juego, creando una representación visual que facilita la interacción del jugador con el juego.

JuegoIntegradov1.c
enemy.c
player.c
Bomb.c
Life.c
projectile.c
ScreenDesign.c
ScreenShows.c
SoundEffect.c
Records.c
GameSymbols.c