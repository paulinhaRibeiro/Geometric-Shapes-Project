#include "matriz_leds.h"
// ****************************************************
// _________________ Bibliotecas para matriz de leds
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "ws2818b.pio.h"
// ________end______ Bibliotecas para matriz de leds
// ****************************************************
//

/*  ***********************************
        Variáveis MATRIZ de LEDs
    **********************************
*/
#define LED_COUNT 25 // Quant. de LEDs
#define LED_PIN 7    // Num Pino

/* ________________________________
        Definição de pixel GRB
   --------------------------------*/
struct pixel_t
{
    uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

/* ________________________________
    Declaração do buffer de pixels
        que formam a matriz.
   --------------------------------*/
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

/*  ***********************************
        DESENHOS NOS LEDs
    **********************************
*/
//     TDs LEDs DESLIGADOS
// --------------------------------
/**
 * Limpa o buffer de pixels.
 */
const uint8_t LEDS_DESLIGADO[][5][5][3] = {
    // TODOS LEDs APAGADOS
    {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    },
};

// ________________________________
//          CARINHA PISCANDO
// --------------------------------
const uint8_t START_FACE[2][5][5][3] = {
    // Frame Carinha Olhos aberto
    {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {129, 0, 255}, {0, 0, 0}, {129, 0, 255}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{245, 117, 162}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {245, 117, 162}},
        {{0, 0, 0}, {245, 117, 162}, {245, 117, 162}, {245, 117, 162}, {0, 0, 0}}},
    // Frame Carinha Olhos fechados
    {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{245, 117, 162}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {245, 117, 162}},
        {{0, 0, 0}, {245, 117, 162}, {245, 117, 162}, {245, 117, 162}, {0, 0, 0}}},
};
// ________________________________
//          FORMAS GEOMÉTRICAS
// --------------------------------
const uint8_t FORMAS_GEOMETRICAS[4][5][5][3] = {
    // Frame Circulo
    {
        {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
        {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255}},
        {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
    },
    // Frame Quadrado
    {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {182, 238, 0}, {182, 238, 0}, {182, 238, 0}, {0, 0, 0}},
        {{0, 0, 0}, {182, 238, 0}, {182, 238, 0}, {182, 238, 0}, {0, 0, 0}},
        {{0, 0, 0}, {182, 238, 0}, {182, 238, 0}, {182, 238, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    },
    // Frame Retângulo
    {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{255, 135, 0}, {255, 135, 0}, {255, 135, 0}, {255, 135, 0}, {255, 135, 0}},
        {{255, 135, 0}, {255, 135, 0}, {255, 135, 0}, {255, 135, 0}, {255, 135, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    },
    // Frame Triângulo
    {
        {{0, 0, 0}, {0, 0, 0}, {0, 255, 165}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 165}, {0, 255, 165}, {0, 255, 165}, {0, 0, 0}},
        {{0, 255, 165}, {0, 255, 165}, {0, 255, 165}, {0, 255, 165}, {0, 255, 165}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    },

};

// ________________________________
//    INDICATIVO DE ACERTO E ERRO
// --------------------------------
const uint8_t ACERTO_ERRO[2][5][5][3] = {
    // Frame V
    {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 41, 255}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 41, 255}, {0, 0, 0}},
        {{0, 41, 255}, {0, 0, 0}, {0, 41, 255}, {0, 0, 0}, {0, 0, 0}},
        {{0, 41, 255}, {0, 41, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    },
    // Frame X
    {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {131, 7, 7}, {0, 0, 0}, {131, 7, 7}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {131, 7, 7}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {131, 7, 7}, {0, 0, 0}, {131, 7, 7}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    },
};

/* ________________________________
            VARIÁVEIS GLOBAIS
        Para contar os ciclos e
            pontuação a cada
                rodada
   --------------------------------*/
int count = 0;    // contas os ciclos - var de controle
float pontos = 0; // Conta os pontos

/*      *******************
            RELACIONADAS
            A MATRIZ DE
                LED
        *******************/
/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin)
{

    // Cria programa PIO.
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;

    // Toma posse de uma máquina PIO.
    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0)
    {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
    }

    // Inicia programa na máquina PIO obtida.
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

    // Limpa buffer de pixels.
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b)
{
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

/**
 * Escreve os dados do buffer nos LEDs.
 */
void npWrite()
{
    // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

// Modificado do github: https://github.com/BitDogLab/BitDogLab-C/tree/main/neopixel_pio
// _____________________________________________________________________
// Função para converter a posição do matriz para uma posição do vetor.
// ---------------------------------------------------------------------
// Função para Mapear Coordenadas XY
int getIndex(int x, int y)
{ // Converte a posição (x, y) da matriz 5x5 para um índice do vetor leds[]
    // Considera o padrão de zigue-zague na numeração dos LEDs.
    // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
    // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
    if (y % 2 == 0)
    {
        return 24 - (y * 5 + x); // Linha par (esquerda para direita).
    }
    else
    {
        return 24 - (y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
    }
}


// Percorre os elementos da lista e chama a função para desenhar na matriz de led
void drawFrame(const uint8_t frame[5][5][3])
{

    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 5; coluna++)
        {
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, frame[coluna][linha][0], frame[coluna][linha][1], frame[coluna][linha][2]);
        }
    }
    npWrite();
}
