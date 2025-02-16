#ifndef BUTTONS_H
#define BUTTONS_H

//
/* ***********************************
        BOTÔES A, B e JOYSTICK
   ***********************************
*/
//          Botão do joystck
// --------------------------------
#define SW_PIN 22

// ________________________________
//    Atraso para debounce em "ms"
// --------------------------------
#define DEBOUNCE_DELAY 50 // Atraso para debounce em milissegundos

// ________________________________
//          Botões A e B
// --------------------------------
#define BUTTON_A_PIN 5 // pino do botão A
#define BUTTON_B_PIN 6 // pino do botão B

// ________________________________
//    RESPOSTAS CORRETAS
// --------------------------------
extern const int RESPOSTAS_CORRETAS[4];

/*      *******************
            CONFIGURA OS
                BOTÕES
        *******************/
extern void setup_buttons();

// __________________________________________
// Função para evitar o debounce de um botão
// ------------------------------------------
extern bool read_stable_button(uint pin);

/*      *******************
            VERIFICA SE
          O USÁRIO GANHOU
              OU NÃO
        *******************/
extern void verifica_acerto(int gpio_pin);

// Quando clicar em um dos botões
extern void click_button(uint8_t *buffer);

#endif