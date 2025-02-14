#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
volatile uint32_t evento = 0;
volatile uint gpio_main = 0;
volatile int btnFlag = 0;

void btn_callback(uint gpio, uint32_t events) {
    btnFlag = 1;
    evento = events;
    gpio_main = gpio;

}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);

  while (true) {
    if (btnFlag){
      if (evento == 0x4) { // fall edge
        if (gpio_main == BTN_PIN_R)
          printf("fall red\n");
        else if (gpio_main == BTN_PIN_G)
          printf("fall green\n");
      }
      btnFlag = 0;
    }
  }
}
