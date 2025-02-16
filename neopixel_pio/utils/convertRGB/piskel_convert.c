// Converte um código hexadecimal gerado no site: https://www.piskelapp.com/
// Para decimal em no padrão RGB.
// O código gerado será utilizado para exibir imagens na matriz de leds neopixel.
#include <stdio.h>

#define FRAMES 8       // indica que tem 8 quadros de imagem
#define MATRIX_ROWS 5  // número de linhas da matriz de pixels
#define MATRIX_COLS 5  // número de colunas da matriz de pixels
#define MATRIX_DEPTH 3 // indica que cada pixel tem três componentes RGB

// Função para converter valores ARGB (0xAARRGGBB) para RGB
// Recebe um valor argb no formato 0xAARRGGBB e extrai os valores RGB
void convertToRGB(int argb, int rgb[3])
{
    rgb[0] = argb & 0xFF;         // Blue - Obtém os 8 últimos bits
    rgb[2] = (argb >> 16) & 0xFF; // Red - Desloca 16 bits à direita
    rgb[1] = (argb >> 8) & 0xFF;  // Green - Desloca 8 bits à direita
}

int main()
{
    // matriz 6x25, onde cada elemento é um valor ARGB
    // 6 quadros de 5×5 pixels
    int argb_values[FRAMES][MATRIX_ROWS * MATRIX_COLS] = {
        {// Carinha - olhos abertos
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xffff0081, 0xff000000, 0xffff0081, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xffa275f5, 0xff000000, 0xff000000, 0xff000000, 0xffa275f5,
         0xff000000, 0xffa275f5, 0xffa275f5, 0xffa275f5, 0xff000000},
        {// Carinha - olhos Fechados
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xffa275f5, 0xff000000, 0xff000000, 0xff000000, 0xffa275f5,
         0xff000000, 0xffa275f5, 0xffa275f5, 0xffa275f5, 0xff000000},
        // Círculo
        {0xff000000, 0xffffffff, 0xff000000, 0xffffffff, 0xff000000,
         0xffffffff, 0xff000000, 0xff000000, 0xff000000, 0xffffffff,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xffffffff, 0xff000000, 0xff000000, 0xff000000, 0xffffffff,
         0xff000000, 0xffffffff, 0xff000000, 0xffffffff, 0xff000000},
        // Quadrado
        {0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xff00eeb6, 0xff00eeb6, 0xff00eeb6, 0xff000000,
         0xff000000, 0xff00eeb6, 0xff00eeb6, 0xff00eeb6, 0xff000000,
         0xff000000, 0xff00eeb6, 0xff00eeb6, 0xff00eeb6, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000},
        // Retângulo
        {0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff0087ff,
         0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff0087ff,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000},
        // Triângulo
        {0xff000000, 0xff000000, 0xffa5ff00, 0xff000000, 0xff000000,
         0xff000000, 0xffa5ff00, 0xffa5ff00, 0xffa5ff00, 0xff000000,
         0xffa5ff00, 0xffa5ff00, 0xffa5ff00, 0xffa5ff00, 0xffa5ff00,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000},
        // X
        {0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xff070783, 0xff000000, 0xff070783, 0xff000000,
         0xff000000, 0xff000000, 0xff070783, 0xff000000, 0xff000000,
         0xff000000, 0xff070783, 0xff000000, 0xff070783, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000},
        // V
        {0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xffff2900,
         0xff000000, 0xff000000, 0xff000000, 0xffff2900, 0xff000000,
         0xffff2900, 0xff000000, 0xffff2900, 0xff000000, 0xff000000,
         0xffff2900, 0xffff2900, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000},
    };

    // Matriz 6x5x5x3 para armazenar os valores RGB após a conversão – matriz de saída RGB
    int rgb_matrix[FRAMES][MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH];

    // Preencher a matriz RGB com a conversão dos valores ARGB
    for (int f = 0; f < FRAMES; f++)
    { // para cada quadro (frame)
        for (int i = 0; i < MATRIX_ROWS * MATRIX_COLS; i++)
        { // Percorre todos os 25 pixels
            int rgb[3];
            // Converte o valor ARGB → RGB
            convertToRGB(argb_values[f][i], rgb);

            // Calcula a posição na matriz 5x5
            int row = i / MATRIX_COLS; // Cálculo da linha - divisão inteira
            int col = i % MATRIX_COLS; // Cálculo da coluna - resto da divisão

            // Armazena os valores convertidos na matriz rgb_matrix 6x5x5x3
            rgb_matrix[f][row][col][0] = rgb[0]; // Red
            rgb_matrix[f][row][col][1] = rgb[1]; // Green
            rgb_matrix[f][row][col][2] = rgb[2]; // Blue
        }
    }

    // Exibi a matriz RGB resultante
    printf("{\n");
    // Formata a saída no terminal como uma matriz tridimensional
    // Cada quadro (frame) é impresso separadamente
    // Os valores {R, G, B} são organizados em uma estrutura para ser usada em exibição de matrizes de LEDs
    for (int f = 0; f < FRAMES; f++)
    {
        printf("  Frame %d:\n  {\n", f + 1);
        for (int i = 0; i < MATRIX_ROWS; i++)
        {
            printf("    { ");
            for (int j = 0; j < MATRIX_COLS; j++)
            {
                printf("{%d, %d, %d}", rgb_matrix[f][i][j][0], rgb_matrix[f][i][j][1], rgb_matrix[f][i][j][2]);
                if (j < MATRIX_COLS - 1)
                {
                    printf(", ");
                }
            }
            printf(" }");
            if (i < MATRIX_ROWS - 1)
            {
                printf(",");
            }
            printf("\n");
        }
        printf("  }\n");
    }
    printf("}\n");

    return 0;
}
