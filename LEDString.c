#include <stdlib.h>
#include <stdio.h>
#include "LEDString.pio.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

int main() {
    sleep_ms(51);
    int red = 0;
    int green = 0;
    int blue = 64;
    int NUMOFPIXELS = 75;

    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    const uint BUTTON_PIN = 18;
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN);




    int DATAPIN = 16;
    PIO pio = pio0;
    uint32_t GRB;
    set_sys_clock_khz(128000, true);
    stdio_init_all();
    uint offset = pio_add_program(pio, &LEDString_program);
    uint sm = pio_claim_unused_sm(pio, true);
    LEDString_program_init(pio, sm, offset, DATAPIN);

    while (true){
        if (gpio_get(BUTTON_PIN)){
          gpio_put(LED_PIN, 1);
          for (size_t i = 0; i < NUMOFPIXELS; i++){
              GRB = (green << 24) | (red << 16) | (blue << 8);
              pio_sm_put_blocking(pio, sm, GRB);
          }
            sleep_ms(500);
            gpio_put(LED_PIN, 0);
        }
    }

   /* PIO pioled = pio1;
    uint offsetled = pio_add_program(pioled, &LEDString_program);
    uint smled = pio_claim_unused_sm(pio, true);*/
    
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
        gpio_put(LED_PIN, 0);
        sleep_ms(1000);
    }
}
