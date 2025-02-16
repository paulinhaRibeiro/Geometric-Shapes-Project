#include <stdio.h>
#include "pico/stdlib.h"

// ****************************************************
// _________________ Bibliotecas para Display Onled
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
// ________end______ Bibliotecas para Display Onled
// ****************************************************

#include "display.h"
#include <src_/matriz_leds/matriz_leds.h>

/*  ***********************************
        Variáveis DISPLAY ONLED
    **********************************
*/
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;
// Perguntas que seram exibidas no display
char *perguntas[4][6] = {
    {"", "1 E Circulo?", "", "  A Sim.", "", "  B Nao."},
    {"", "2 Qual forma e?", "", "  A Circulo.", "", "  B Quadrado."},
    {"", "3 E Quadrado?", "", "  A Sim.", "", "  B Nao."},
    {"", "4 Qual forma e?", "", "  A Triangulo.", "", "  B Circulo."}};

// Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

// Configura o Display
void init_oled_display()
{
    //  ________________DISPLAY ONLED______________________
    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    calculate_render_area_buffer_length(&frame_area);
}

// Apaga o display
void zerar_display(uint8_t *buffer)
{
    // Zera o display
    memset(buffer, 0, ssd1306_buffer_length);
    render_on_display(buffer, &frame_area);
}

// Escreve as perguntas na tela
void desenhar_display(uint8_t *buffer)
{
    int y = 0;

    for (size_t j = 0; j < count_of(perguntas[count]); j++)
    {
        ssd1306_draw_string(buffer, 5, y, perguntas[count][j]);
        y += 8;
    }
    render_on_display(buffer, &frame_area);
}

// escreve a pontuação do jogador no display
void score_gamer(uint8_t *buffer)
{
    char quantPontos[10];
    sprintf(quantPontos, "Pontos: %.1f", pontos); // Formata o float na string corretamente
                                                  // Desenha na tela a pontuação
    ssd1306_draw_string(buffer, 5, 0, quantPontos);
    render_on_display(buffer, &frame_area);
}
