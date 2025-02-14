#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED = 4;

volatile int btn_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) {         // fall edge
    btn_flag = 1;
  
  } 
  else if (events == 0x8) {  // rise edge 
}
}


int main() {
  stdio_init_all();
  // Inicializando o LED 

  gpio_init(LED);
  gpio_set_dir(LED, GPIO_OUT);
  
  // Inicializando o Botão 

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  
  bool estado_led = false;

  while (true) {

    if (btn_flag){
      estado_led = !estado_led;
      gpio_put(LED , estado_led);
      btn_flag = 0;
    }
  }
}
