#include "pico/stdlib.h"
#include "matriz_led.h"
#include "stdio.h"
#include "numeros.h"

const uint led_pin = 13;    // Green=11, Blue=12, Red=13


void init_led() {
//Inicializações
    gpio_init(led_pin);                 // Inicializa o pino 13 do LED
    gpio_set_dir(led_pin, GPIO_OUT);    // Configura o pino 13 como saída
    gpio_put(led_pin, 0);               // Garante que o LED vermelho inicie apagado
}

// TODO:O LED vermelho do LED RGB deve piscar continuamente 5 vezes por segundo.
void piscar_led_vermelho() {
    gpio_put(led_pin, 1);
    sleep_ms(100);
    gpio_put(led_pin, 0);
    sleep_ms(100);
}
//TODO: Os LEDs WS2812 devem ser usados para criar efeitos visuais representando números de 0 a 9.
void imprimir_numero(const uint8_t numero[][2], size_t tamanho, uint8_t r, uint8_t g, uint8_t b) {
    npClear();  // Limpa a matriz de LEDs

    // Acende os LEDs conforme as posições do número
    for (size_t i = 0; i < tamanho; i++) {
        int x = numero[i][0];
        int y = numero[i][1];
        int indice = obterIndice(x, y);

        // Define a cor do LED no índice correspondente
        npSetLED(indice, r, g, b);

    }
npWrite();  // Atualiza os LEDs com a nova configuração

    // sleep_ms(500);
    // npClear();
    // npWrite();
}
int main()
{
    init_led();
    // inicializa WS2812 
    npInit(LED_PIN_WS2812);
    // Loop principal
    imprimir_numero(NUMERO_9, sizeof(NUMERO_9) / sizeof(NUMERO_9[0]), 255, 0, 0);
    while (true) {
        piscar_led_vermelho();
    }
}