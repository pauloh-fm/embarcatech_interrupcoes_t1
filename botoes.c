#include "pico/stdlib.h"
const uint botao_a = 5; // Botão A GPIO5
const uint botao_b = 6; // Botão B GPIO6
void init_botoes(uint botao_pin) {
    gpio_init(botao_pin);
    gpio_set_dir(botao_pin, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(botao_pin); // Habilita o pull-up interno
}
