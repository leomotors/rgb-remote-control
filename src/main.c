#include <stdio.h>

#include "get.h"
#include "models.h"

int main() {
    rgb_config config = api_get_config();

    printf("Parsed config:\n");
    printf("gpio_fan_mode: %d\n", config.gpio_fan_mode);
    printf("gpio_fan_pin: %d\n", config.gpio_fan_pin);
    printf("rgb_brightness: %d\n", config.rgb_brightness);
    printf("rgb_color: %s\n", config.rgb_color);
    printf("rgb_enable: %d\n", config.rgb_enable);
    printf("rgb_led_count: %d\n", config.rgb_led_count);
    printf("rgb_speed: %d\n", config.rgb_speed);
    printf("rgb_style: %s\n", config.rgb_style);
    printf("temperature_unit: %s\n", config.temperature_unit);

    free_rgb_config(config);
}
