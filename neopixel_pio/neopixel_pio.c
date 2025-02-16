#include <stdio.h>
#include "pico/stdlib.h"
//
#include "src_/buzzer/buzzer.h"
#include "hardware/pwm.h"
//
#include "src_/matriz_leds/matriz_leds.h"
#include "src_/buttons/buttons.h"
//
#include "src_/display/display.h"
#include "inc/ssd1306_i2c.h"

/* ____________________ Função Principal     ____________________*/
int main()
{
    // Verificar quando iniciar o jogo
    bool state_button_joystick = false;

    // Inicializa entradas e saídas.
    stdio_init_all();
    setup_buttons();

    // // config buzzer
    config_pwm_buzzer(); // Configura o PWM para o buzzer

    // Inicializa matriz de LEDs NeoPixel.
    npInit(LED_PIN);

    // _______________
    // Inicializa o display
    init_oled_display();
    // Buffer do display
    uint8_t ssd[ssd1306_buffer_length];

    // zera o display inteiro
    zerar_display(ssd);

    // Loop infinito.
    while (true)
    {
        // ___________________Momento inicial,
        // enquanto não clicar no botão do joystick, não vai para as forma geometricas.
        while (state_button_joystick == false)
        {
            for (size_t i = 0; i < 2; i++)
            {
                if (read_stable_button(SW_PIN))
                {
                    while (gpio_get(SW_PIN) == 0)
                        ; // Aguarda soltar o botão
                    state_button_joystick = true;
                    drawFrame(LEDS_DESLIGADO[0]);
                    sleep_ms(75);

                    // _____________ Repetindo as formas geometricas
                    drawFrame(FORMAS_GEOMETRICAS[count]);
                    sleep_ms(75);
                    // ________END__ Repetindo as formas geometricas

                    // _EXIBIR 1 Questão Display
                    // zera o display inteiro
                    zerar_display(ssd);
                    sleep_ms(75);
                    //  DESENHA NA TELA
                    desenhar_display(ssd);
                    sleep_ms(75);
                    break;
                }

                drawFrame(START_FACE[i]);
                sleep_ms(300);
            }
        }
        // __________END______Momento inicial

        // ____________________________________________
        // __________________ BOTÂO A _________________
        // --------------------------------------------
        // Se clicar no botão A
        if (read_stable_button(BUTTON_A_PIN))
        {
            while (gpio_get(BUTTON_A_PIN) == 0)
                ; // Aguarda soltar o botão

            verifica_acerto(BUTTON_A_PIN);

            click_button(ssd);
        }
        // _________END______ BOTÂO A

        // ____________________________________________
        // __________________ BOTÂO B _________________
        // --------------------------------------------
        // Se clicar no botão B
        if (read_stable_button(BUTTON_B_PIN))
        {
            while (gpio_get(BUTTON_B_PIN) == 0)
                ; // Aguarda soltar o botão
            verifica_acerto(BUTTON_B_PIN);
            sleep_ms(100);
            // Para não ficar chamando sempre o desenho no led e somente se o contador for menor q o tamanho da lista.
            click_button(ssd);
        }
        // _________END______ BOTÂO A

        // _______________ RESTART PERGUNTAS
        if (count == count_of(RESPOSTAS_CORRETAS))
        {              // contador maior que tamanho da lista
            count = 0; // reseta o contador
            state_button_joystick = false;
            drawFrame(LEDS_DESLIGADO[0]);

            // Deixa o led desligado por 6 segundos
            sleep_ms(100);

            // zera o display inteiro
            zerar_display(ssd);
            // escreve a pontuação na tela
            score_gamer(ssd);
            pontos = 0; // resenta a pontuação
            sleep_ms(75);
            sleep_ms(4000);

            // zera o display inteiro
            zerar_display(ssd);
            sleep_ms(1000);
        }
        // ______END_______ RESTART PERGUNTAS

        sleep_ms(10);
    }
}
