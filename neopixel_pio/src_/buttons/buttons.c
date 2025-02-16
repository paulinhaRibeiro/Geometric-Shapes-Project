#include <stdio.h>
#include "pico/stdlib.h"
#include "buttons.h"
#include <src_/matriz_leds/matriz_leds.h>
#include <src_/buzzer/buzzer.h>
#include <src_/display/display.h>

// ________________________________
//    RESPOSTAS CORRETAS
// --------------------------------
const int RESPOSTAS_CORRETAS[4] = {5, 6, 6, 5};

/*      *******************
            RELACIONADAS
            AOS BOTÕES
        *******************/
// Quando clicar em um dos botões
void click_button(uint8_t *buffer)
{
    // Para não ficar chamando sempre o desenho no led e somente se o contador for menor q o tamanho da lista.
    if (count < count_of(RESPOSTAS_CORRETAS))
    {
        sleep_ms(100);
        // _____________ Desenhar a formas geometricas
        drawFrame(FORMAS_GEOMETRICAS[count]);
        // ________END__ Desenhar a formas geometricas

        sleep_ms(75);
        // zera o display inteiro
        zerar_display(buffer);
        sleep_ms(75);

        //  DESENHA NA TELA
        desenhar_display(buffer);
        sleep_ms(75);
    }
}
void verifica_acerto(int gpio_pin)
{
    // DESLIGAR TODOS OS LEDS
    drawFrame(LEDS_DESLIGADO[0]);
    sleep_ms(10);

    if (RESPOSTAS_CORRETAS[count] == gpio_pin)
    {

        drawFrame(ACERTO_ERRO[0]);
        play_success_tone();
        pontos += 2.5;
    }
    else
    {

        drawFrame(ACERTO_ERRO[1]);
        play_error_tone();
    }
    sleep_ms(1000);
    count++;
}

// __________________________________________
// Função para evitar o debounce de um botão
// ------------------------------------------
bool read_stable_button(uint pin)
{
    if (gpio_get(pin) == 0)
    {                              // Verifica se o botão foi pressionado (ativo em LOW)
        sleep_ms(DEBOUNCE_DELAY);  // Espera um tempo para evitar ruídos
        return gpio_get(pin) == 0; // Confirma se o botão ainda está pressionado
    }
    return false;
}

/*      *******************
            CONFIGURA OS
                BOTÕES
        *******************/
void setup_buttons()
{
    // __________ JOYSTICK
    // Inicializa o pino do botão do joystick
    gpio_init(SW_PIN);
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_pull_up(SW_PIN);

    // __________ BOTÃO A e B
    // Inicializa o pino do botões
    gpio_init(BUTTON_A_PIN); // inicializa o botão A
    gpio_init(BUTTON_B_PIN); // inicializa o botão b

    // Definir a direção dos Pinos dos botões
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN); // O Botão A vai ser entrada
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN); // Botão B vai ser de entrada

    // Habilitar resistores de pull-up
    gpio_pull_up(BUTTON_A_PIN); // Habilita o resistor de Pull-up externo associado ao pino do BOTÃO A
    gpio_pull_up(BUTTON_B_PIN); // Habilita o resistor de Pull-up externo associado ao pino do BOTÃO B
};
