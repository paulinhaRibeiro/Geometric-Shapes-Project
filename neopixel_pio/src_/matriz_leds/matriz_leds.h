#ifndef MATRIZ_LEDS_H
#define MATRIZ_LEDS_H

#include <stdio.h>
#include "pico/stdlib.h"

/*      *******************
            DEFINIÇÕES
        *******************/
// ________________________________
//    Num Pino
// --------------------------------
#define LED_PIN 7

/* ________________________________
            VARIÁVEIS GLOBAIS
        Para contar os ciclos e
            pontuação a cada
                rodada
   --------------------------------*/
extern int count;    // contas os ciclos - var de controle
extern float pontos; // Conta os pontos

// ________________________________
//         TDs LEDs DESLIGADOS
// --------------------------------
extern const uint8_t LEDS_DESLIGADO[][5][5][3];

// ________________________________
//          FORMAS GEOMÉTRICAS
// --------------------------------
extern const uint8_t FORMAS_GEOMETRICAS[4][5][5][3];

// ________________________________
//          CARINHA PISCANDO
// --------------------------------
extern const uint8_t START_FACE[2][5][5][3];

// ________________________________
//    INDICATIVO DE ACERTO E ERRO
// --------------------------------
extern const uint8_t ACERTO_ERRO[2][5][5][3];

/*      *******************
            PROTÓTIPOS DE
              FUNÇÔES
        *******************/
/* ________________________________
        Inicializa a máquina PIO
        para controle da matriz
                de LEDs.
   --------------------------------*/
extern void npInit(uint pin);


// __________________________________________
//        Funçao para Percorrer cada
//        elemento da lista e mandar
//        desenhar na matriz de leds
// ------------------------------------------
extern void drawFrame(const uint8_t frame[5][5][3]);

#endif