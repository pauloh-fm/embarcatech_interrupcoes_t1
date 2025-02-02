#include <stdint.h>

// Definição dos arrays como 'static const' para ter ligação interna.
static const uint8_t NUMERO_1[][2] = {
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}
};

static const uint8_t NUMERO_2[][2] = {
    {1, 0}, {2, 0}, {3, 0}, {3, 1}, {3, 2},
    {2, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 4}
};

static const uint8_t NUMERO_3[][2] = {
    {1, 0}, {2, 0}, {3, 0}, {3, 1}, {3, 2},
    {2, 2}, {3, 3}, {3, 4}, {1, 4}, {2, 4}
};

static const uint8_t NUMERO_4[][2] = {
    {3, 0}, {3, 1}, {1, 1}, {1, 0}, {1, 2},
    {2, 2}, {3, 2}, {3, 3}, {3, 4}
};

static const uint8_t NUMERO_5[][2] = {
    {1, 0}, {2, 0}, {3, 0}, {1, 1}, {1, 2},
    {2, 2}, {3, 2}, {3, 3}, {1, 4}, {2, 4}, {3, 4}
};

static const uint8_t NUMERO_6[][2] = {
    {1, 0}, {2, 0}, {3, 0}, {1, 1}, {1, 2},
    {2, 2}, {3, 2}, {1, 3}, {3, 3}, {1, 4}, {2, 4}, {3, 4}
};

static const uint8_t NUMERO_7[][2] = {
    {1, 0}, {2, 0}, {3, 0}, {3, 1}, {3, 2},
    {3, 3}, {3, 4}
};

static const uint8_t NUMERO_8[][2] = {
    {1, 0}, {2, 0}, {3, 0}, {1, 1}, {3, 1},
    {1, 2}, {2, 2}, {3, 2}, {1, 3}, {3, 3},
    {1, 4}, {2, 4}, {3, 4}
};

static const uint8_t NUMERO_9[][2] = {
    {1, 0}, {2, 0}, {3, 0}, {1, 1}, {3, 1},
    {1, 2}, {2, 2}, {3, 2}, {3, 3}, {1, 4},
    {2, 4}, {3, 4}
};

typedef struct {
    const uint8_t (*numero)[2];  // Ponteiro para o array bidimensional do número
    size_t tamanho;              // Número de elementos (pares x,y)
} Numero;

// Criação do array que agrupa os números
static const Numero numeros[9] = {
    { NUMERO_1, sizeof(NUMERO_1) / sizeof(NUMERO_1[0]) },
    { NUMERO_2, sizeof(NUMERO_2) / sizeof(NUMERO_2[0]) },
    { NUMERO_3, sizeof(NUMERO_3) / sizeof(NUMERO_3[0]) },
    { NUMERO_4, sizeof(NUMERO_4) / sizeof(NUMERO_4[0]) },
    { NUMERO_5, sizeof(NUMERO_5) / sizeof(NUMERO_5[0]) },
    { NUMERO_6, sizeof(NUMERO_6) / sizeof(NUMERO_6[0]) },
    { NUMERO_7, sizeof(NUMERO_7) / sizeof(NUMERO_7[0]) },
    { NUMERO_8, sizeof(NUMERO_8) / sizeof(NUMERO_8[0]) },
    { NUMERO_9, sizeof(NUMERO_9) / sizeof(NUMERO_9[0]) }
};
