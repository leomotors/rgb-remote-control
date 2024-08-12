#include <stdio.h>
#include <time.h>

#include "constants.h"
#include "get.h"
#include "handler.h"
#include "models.h"
#include "remote.h"

signed int latest_code = 0;
time_t latest_time = 0;

static void remote_handler(signed int code) {
    time_t now = time(NULL);

    if (now - latest_time < 1 && code == latest_code) {
        // Debounce
        return;
    }

    latest_code = code;
    latest_time = now;

    switch (code) {
        case OK: {
            rgb_config config = api_get_config();
            handle_toggle_rgb(config);
            free_rgb_config(config);
            break;
        }

        case UP: {
            rgb_config config = api_get_config();
            handle_increase_brightness(config);
            free_rgb_config(config);
            break;
        }

        case DOWN: {
            rgb_config config = api_get_config();
            handle_decrease_brightness(config);
            free_rgb_config(config);
            break;
        }
    }
}

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

    int exit_code = start_listening_remote(remote_handler);
    return exit_code;
}
