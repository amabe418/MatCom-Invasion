# Nombre del compilador
CC = gcc

# Flags para el compilador
CFLAGS = -lncurses -pthread

# Archivos de encabezado
HEADERS = Enemy.h Projectile.h Player.h ScreenDesign.h global.h

# Archivos fuente
SRCS = juegoIntegradoV1.c Enemy.c Projectile.c Player.c ScreenDesign.c global.c

# Archivos objeto
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
EXEC = game

# Regla por defecto para compilar y ejecutar
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Regla para compilar los archivos .c a .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos compilados
clean:
	rm -f $(OBJS) $(EXEC)

# Regla para ejecutar el juego
run: $(EXEC)
	./$(EXEC)
