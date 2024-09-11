#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "SoundEffect.h"

pid_t GameOverSoundPID;
pid_t ExplosionSoundPID;
pid_t ShootSoundPID;
pid_t BombSoundPID;
pid_t LifeSoundPID;

#define GameOverFileName "sound/game_over_1.wav"
#define ExplosionFileName "sound/impact-152508.wav"
#define ShootFileName "sound/shoot02wav-14562.wav"
#define BombFileName "sound/bomb.wav"
#define LifeFileName "sound/life_1.wav"

// void playBackgroundSound(int soundType) {
//     const char *filename;
//     pid_t *soundPID;

//     switch (soundType) {
//         case 1:
//             filename = GameOverFileName;
//             soundPID = &GameOverSoundPID;
//             break;
//         case 2:
//             filename = ExplosionFileName;
//             soundPID = &ExplosionSoundPID;
//             break;
//         case 3:
//             filename = ShootFileName;
//             soundPID = &ShootSoundPID;
//             break;
//         case 4:
//             filename = BombFileName;
//             soundPID = &BombSoundPID;
//         break;
//         case 5:
//             filename = LifeFileName;
//             soundPID = &LifeSoundPID;
//         break;
//         default:
//         return; // Si el tipo de sonido no es válido, salir de la función
//     }

//     // Verifica si el archivo existe y es legible
//     if (access(filename, F_OK) == -1) {
//         // perror("Error: No se puede acceder al archivo de sonido");
//         *soundPID = -1; // Indica que el proceso no se creó
//         return;
//     }

//     pid_t pid = fork();  // Crea un proceso hijo
//     if (pid == 0) {  // Este es el proceso hijo
//             // Redirige la salida estándar y de error a /dev/null
//             //Para silenciar cualquier mensaje que pueda mandar este proceso a la consola
//         freopen("/dev/null", "w", stdout);
//         freopen("/dev/null", "w", stderr);


//         execlp("aplay", "aplay", filename, NULL);  // Reproduce el archivo de sonido usando aplay
//         // perror("Error: Fallo al ejecutar aplay");
//         exit(1);  // Termina el proceso hijo con un error si falla aplay
//     } else if (pid > 0) {  // Este es el proceso padre
//         *soundPID = pid;  // Guarda el PID del proceso hijo en la variable correspondiente
//     } else {  // Error en fork
//         // perror("Error: Fallo al crear proceso hijo");
//         *soundPID = -1; // Indica que el proceso no se creó
//     }
// }

void playBackgroundSound(int soundType) {
    const char *filename;
    pid_t *soundPID;

    switch (soundType) {
        case 1:
            filename = GameOverFileName;
            soundPID = &GameOverSoundPID;
            break;
        case 2:
            filename = ExplosionFileName;
            soundPID = &ExplosionSoundPID;
            break;
        case 3:
            filename = ShootFileName;
            soundPID = &ShootSoundPID;
            break;
        case 4:
            filename = BombFileName;
            soundPID = &BombSoundPID;
            break;
        case 5:
            filename = LifeFileName;
            soundPID = &LifeSoundPID;
            break;
        default:
            return; // Si el tipo de sonido no es válido, salir de la función
    }

    // Verifica si el archivo existe y es legible
    if (access(filename, F_OK) == -1) {
        // perror("Error: No se puede acceder al archivo de sonido");
        *soundPID = -1; // Indica que el proceso no se creó
        return;
    }

    pid_t pid = fork();  // Crea un proceso hijo
    if (pid == 0) {  // Este es el proceso hijo
        // Redirige la salida estándar y de error a /dev/null
        // Para silenciar cualquier mensaje que pueda mandar este proceso a la consola
        freopen("/dev/null", "w", stdout);
        freopen("/dev/null", "w", stderr);

        // Usa paplay en lugar de aplay para reproducir el archivo de sonido
        execlp("paplay", "paplay", filename, NULL);  // Reproduce el archivo de sonido usando paplay
        // perror("Error: Fallo al ejecutar paplay");
        exit(1);  // Termina el proceso hijo con un error si falla paplay
    } else if (pid > 0) {  // Este es el proceso padre
        *soundPID = pid;  // Guarda el PID del proceso hijo en la variable correspondiente
    } else {  // Error en fork
        // perror("Error: Fallo al crear proceso hijo");
        *soundPID = -1; // Indica que el proceso no se creó
    }
}
