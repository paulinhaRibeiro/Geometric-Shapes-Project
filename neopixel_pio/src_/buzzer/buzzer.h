
#ifndef BUZZER_H
#define BUZZER_H

/*  ***********************************
        Variáveis PWM - BUZZER
    ***********************************/
#define BUZZER_PIN 10 // Pino do buzzer
#define CLOCK_PWM 125000000
#define PWM_DIVIDER 100.0

extern void play_success_tone(uint slice);
extern void play_error_tone(uint slice);
#endif