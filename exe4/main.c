#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

int BTN_VERDE = 26;
int BTN_VERMELHO = 28;

int LED_VERDE = 6;
int LED_VERMELHO = 4;

volatile uint32_t evento = 0;
volatile uint gpio_main = 0;
volatile btnFlag = 0;

void btn_callback(uint gpio, uint32_t events) {
  gpio_main = gpio;
  evento = events;
  btnFlag = 1;

}


int main() {
  stdio_init_all();


  // Inicializando Botões

  gpio_init(BTN_VERMELHO);
  gpio_set_dir(BTN_VERMELHO, GPIO_IN);
  gpio_pull_up(BTN_VERMELHO);

  gpio_init(BTN_VERDE);
  gpio_set_dir(BTN_VERDE, GPIO_IN);
  gpio_pull_up(BTN_VERDE);

  // Inicializando os Leds 

  gpio_init(LED_VERDE);
  gpio_set_dir(LED_VERDE, GPIO_OUT);

  
  gpio_init(LED_VERMELHO);
  gpio_set_dir(LED_VERMELHO, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  
  bool estado_led_vermelho = false;
  bool estado_led_verde = false;
  while (true) {

    if (btnFlag){
      if (evento == 0x4) { // fall edge
        if (gpio_main == BTN_VERMELHO)
          estado_led_vermelho = !estado_led_vermelho;
          gpio_put(LED_VERMELHO , estado_led_vermelho);
      }
      if (evento == 0x8) { // rise edge
        if (gpio_main == BTN_VERDE)
          estado_led_verde = !estado_led_verde;
          gpio_put(LED_VERDE , estado_led_verde);
      }
      btnFlag = 0;
    }
  }
}
