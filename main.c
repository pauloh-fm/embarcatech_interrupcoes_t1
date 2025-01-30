#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2818b.pio.h"
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
int main()
{
    init_led();

    // Loop principal
    while (true) {
        piscar_led_vermelho();
    }
}