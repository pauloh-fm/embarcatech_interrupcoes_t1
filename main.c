#include "pico/stdlib.h"
#include "matriz_led.h"
#include "stdio.h"
#include "numeros.h"
#include "botoes.h"
#include <stdio.h>
const uint led_pin = 13;    // Green=11, Blue=12, Red=13

int numero_atual = 0;
volatile bool incrementar_flag = false;     // Flag setada na interrupção para atualizar a matriz

// Para debounce: guarda o instante (em microssegundos) da última interrupção processada
static volatile uint32_t last_irq_time = 0;

// Protótipo do callback da interrupção
static void interrupcao_incrementar(uint gpio, uint32_t events);
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
    npClear();
    for (size_t i = 0; i < tamanho; i++) {
        int x = numero[i][0];
        int y = numero[i][1];
        int indice = obterIndice(x, y);
        npSetLED(indice, r, g, b);
    }
    npWrite();
}
// TODO: Função que verifica se o botão A foi pressionado e, se sim, incrementa o número exibido
void incrementar_numero(void) {
    imprimir_numero(numeros[numero_atual].numero,
                     numeros[numero_atual].tamanho,
                     128, 0, 0);
}
static void interrupcao_incrementar(uint gpio, uint32_t events) {
    if (gpio == botao_a) {
        // Incrementa o número, ciclando de 9 para 0
        numero_atual++;
        if (numero_atual >= 9) numero_atual = 0;
        incrementar_flag = true;
    }
}
// TODO: Função para fazer o botão B decrementar em 1 o numero de 0 a 9.
int main()
{
    init_led();
    // inicializa WS2812 
    npInit(LED_PIN_WS2812);
    // Loop principal
    init_botoes(botao_a);
    init_botoes(botao_b);
printf("salve\n");
 gpio_set_irq_enabled_with_callback(botao_a, GPIO_IRQ_EDGE_FALL, true, interrupcao_incrementar);
while (true) {
        piscar_led_vermelho();  // Pisca o LED de status

        // Se a flag de atualização estiver ativa, atualiza a matriz de LEDs
        if (incrementar_flag) {
            printf("incrementar_flag ativada, exibindo número: %d\n", numero_atual);
            incrementar_numero();
            incrementar_flag = false;
        }
    }
    
    return 0;
}