#ifndef CONTROL_H
#define CONTROL_H
#include "esp32-hal-touch.h"
#include <Arduino.h>

extern const int touchPin; // El pin que se usará para el sensor táctil
extern const int bocinaPin; // El pin conectado al relé para la bocina
extern const int contactorPin; // El pin conectado al relé-contactor para cortar la energía
extern const int threshold; // Umbral de sensibilidad del sensor táctil
extern const int numReadings; // Número de lecturas para la media móvil

extern unsigned long timeThresholdMet; // Almacena el momento en que se cumple el umbral
extern unsigned long lastToggleTime; // La última vez que el estado de la bocina cambió
extern int stage; // Etapa actual de la alarma
extern bool bocinaState; // Estado actual de la bocina (HIGH o LOW)
extern bool contactorState ; // Estado del relé-contactor (HIGH o LOW)
extern int readings[]; // Array para almacenar las lecturas
extern int readIndex; // Índice actual para el próximo dato
extern int total; // Suma total de las lecturas
extern int average; // Promedio de las lecturas

//Function declarations:

void control_init();
void control_update();


#endif