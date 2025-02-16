#include <stdio.h>
#include "pico/stdlib.h"
// ****************************************************
// _________________ Bibliotecas para pwm - BUZZER
#include "hardware/pwm.h"
#include "buzzer.h"
// ________end______ Bibliotecas para pwm - BUZZER
// ****************************************************


/*      *******************
            CONFIGURA O
              PWM PARA O
              BUZZER
        *******************/
void config_pwm_buzzer()
{
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);   // Configura o pino como PWM
    uint slice = pwm_gpio_to_slice_num(BUZZER_PIN); // Obtem o slice PWM do pino
    pwm_set_clkdiv(slice, PWM_DIVIDER);             // Aplica o divisor de clock
    pwm_set_enabled(slice, true);                   // Habilita o PWM
}


// Função para tocar um tom no buzzer
void play_tone(int frequency, int duration) {
    uint slice = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint32_t wrap = CLOCK_PWM / (frequency * PWM_DIVIDER);  // Cálculo do wrap
    pwm_set_wrap(slice, wrap);  // Define o wrap para a frequência
    pwm_set_gpio_level(BUZZER_PIN, wrap / 2);  // Define o duty cycle

    sleep_ms(duration);  // Toca o tom pelo tempo especificado
    pwm_set_gpio_level(BUZZER_PIN, 0);  // Desliga o buzzer
}


// Função para tocar tom de sucesso
void play_success_tone() {
    play_tone(1000, 200);  // Toca um tom de 1000 Hz por 200ms
    play_tone(1200, 200);  // Toca um tom de 1200 Hz por 200ms
    play_tone(1400, 300);  // Toca um tom de 1400 Hz por 300ms
}

// Função para tocar tom de erro
void play_error_tone() {
    play_tone(400, 300);   // Toca um tom de 400 Hz por 300ms
    play_tone(300, 300);   // Toca um tom de 300 Hz por 300ms
}
