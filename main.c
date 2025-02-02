#include "pico/stdlib.h"
#include "matriz_led.h"
#include "numeros.h"
#include "botoes.h"
#include "hardware/timer.h"
#include <stdio.h>

const uint led_pin = 13;    // led_red

// Número atual exibido (de 0 a 8)
int numero_atual = 0;
// Flag para sinalizar que houve atualização (incremento ou decremento)
volatile bool atualizar_flag = false;

// Variáveis de debounce  para cada botão
static volatile uint32_t last_irq_time_inc = 0;
static volatile uint32_t last_irq_time_dec = 0;

// Inicializa o LED RGB 
void init_led(void) {
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_put(led_pin, 0);
}

// O LED vermelho deve piscar continuamente 5 vezes por segundo
void piscar_led_vermelho(void) {
    gpio_put(led_pin, 1);
    sleep_ms(100);
    gpio_put(led_pin, 0);
    sleep_ms(100);
}

// Exibe um número na matriz de LEDs WS2812
void imprimir_numero(const uint8_t numero[][2], size_t tamanho, uint8_t r, uint8_t g, uint8_t b) {
    npClear();
    for (size_t i = 0; i < tamanho; i++) {
        int x = numero[i][0];
        int y = numero[i][1];
        int indice = obterIndice(x, y);
        npSetLED(indice, r, g, b);
    }
    npWrite();
}

// Atualiza a matriz exibindo o número atual com a cor vermelha (valor 128 no canal R)
void atualizar_numero(void) {
    imprimir_numero(numeros[numero_atual].numero,
                    numeros[numero_atual].tamanho,
                    128, 0, 0);
}

// Callback global para interrupções dos botões A e B
static void gpio_callback(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (gpio == botao_a) {
        // Debounce: ignora se menos de 200 ms se passaram
        if (current_time - last_irq_time_inc < 200000) return;
        last_irq_time_inc = current_time;
        // Incrementa o número (ciclo de 0 a 8)
        numero_atual++;
        if (numero_atual > 9) {
            numero_atual = 0;
        }
        atualizar_flag = true;
    }
    else if (gpio == botao_b) {
        // Debounce: ignora se menos de 200 ms se passaram
        if (current_time - last_irq_time_dec < 200000) return;
        last_irq_time_dec = current_time;
        // Decrementa o número (ciclo de 0 a 9)
        numero_atual--;
        if (numero_atual < 0) {
            numero_atual = 9;
        }
        atualizar_flag = true;
    }
}

int main(void) {
    stdio_init_all(); // Inicializa a comunicação serial (USB)
    
    // Inicializações gerais
    init_led();
    npInit(LED_PIN_WS2812);
    init_botoes(botao_a);
    init_botoes(botao_b);

    printf("Sistema iniciado!\n");

    // Registra a callback global para as interrupções.
    gpio_set_irq_enabled_with_callback(botao_a, GPIO_IRQ_EDGE_FALL, true, gpio_callback);
    // Habilita a interrupção para o botão B;
    gpio_set_irq_enabled(botao_b, GPIO_IRQ_EDGE_FALL, true);

    while (true) {
        piscar_led_vermelho();  // Pisca o LED de status

        // Se houve atualização (incremento ou decremento), atualiza a matriz de LEDs
        if (atualizar_flag) {
            printf("Atualizando, exibindo número: %d\n", numero_atual);
            atualizar_numero();
            atualizar_flag = false;
        }
    }
    
    return 0;
}
