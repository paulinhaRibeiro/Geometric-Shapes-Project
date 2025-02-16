# **Aprendendo Formas Geométricas com a BitDogLab**

## 📖 **Descrição**
Este projeto é uma aplicação educacional interativa desenvolvida para ensinar crianças a reconhecer e aprender formas geométricas básicas. O jogo roda na placa **BitDogLab**, que contém um **Raspberry Pi Pico W**, e foi totalmente escrito na linguagem **C**.

## 🎥 Demonstração  
![Vídeo do Jogo](video_demostrativo/projeto.mp4)


## 🔧 **Recursos Utilizados**
O sistema faz uso dos seguintes componentes da **BitDogLab**:

- **🎮 Botões A, B e botão SW do Joystick** - usados para navegação e seleção de respostas.
- **🔊 Buzzer passivo B** - utilizado para feedback sonoro em acertos e erros.
- **💡 Matriz de LEDs RGB 5x5 (WS2812B - Neopixel)** - exibe as formas geométricas e feedbacks visuais.
- **📺 Display OLED (0,96 polegadas, 128x64, I2C)** - apresenta as perguntas e a pontuação final.

## 🎮 **Funcionamento**
1. Para iniciar o jogo, a criança deve pressionar o botão **SW do Joystick**.
2. A **matriz de LEDs RGB** exibe as formas geométricas básicas (**triângulo, retângulo, quadrado ou círculo**).
3. A criança deve selecionar a resposta correta pressionando um dos **botões A ou B**.
4. Se errar, a **matriz de LEDs** exibe um **“X”**, e um som de erro é emitido pelo **buzzer**.
5. Se acertar, a **matriz de LEDs** exibe um **sinal de acerto**, e um som de acerto é emitido pelo **buzzer**.
6. O **display OLED** exibe as perguntas e a **pontuação final** ao término do quiz.

## ⚙️ **Requisitos**
- 🛠️ Placa **BitDogLab** com **Raspberry Pi Pico W**.
- 💻 Código escrito em **C**, compatível com a plataforma.
- 📚 Biblioteca para controle do **display OLED** (`ssd1306.h`).
- 💡 Biblioteca para controle da **matriz de LEDs WS2812B**.

## 📩 **Autor e Contribuição**
Este projeto foi desenvolvido como parte de um estudo em **sistemas embarcados e IoT**. Contribuições e sugestões são bem-vindas!

📌 **Autor:** Paula Ribeiro 
📜 **Licença:** **MIT**


