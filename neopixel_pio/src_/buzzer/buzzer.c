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
void play_tone(uint pin, uint slice, int frequency, int duration)
{
    // config buzzer
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice1 = pwm_gpio_to_slice_num(BUZZER_PIN);

    uint32_t wrap = (uint32_t)CLOCK_PWM / (frequency * PWM_DIVIDER);
    pwm_set_wrap(slice1, wrap);
    pwm_set_clkdiv(slice1, PWM_DIVIDER);
    pwm_set_gpio_level(BUZZER_PIN, wrap / 2);
    pwm_set_enabled(slice1, true);
    sleep_ms(duration);
    pwm_set_enabled(slice1, false);
    sleep_ms(50); // Pequena pausa entre as notas
}

void play_success_tone(uint slice)
{
    play_tone(BUZZER_PIN, slice, 1000, 200);
    play_tone(BUZZER_PIN, slice, 1200, 200);
    play_tone(BUZZER_PIN, slice, 1400, 300);
}

void play_error_tone(uint slice)
{
    play_tone(BUZZER_PIN, slice, 400, 300);
    play_tone(BUZZER_PIN, slice, 300, 300);
}
