#include "handler.h"

#include "models.h"
#include "post.h"

void handle_toggle_rgb(rgb_config config) {
    if (config.gpio_fan_mode == 0) {
        config.gpio_fan_mode = 2;
    } else {
        config.gpio_fan_mode = 0;
    }

    api_set_config(config);
}

void handle_increase_brightness(rgb_config config) {
    if (config.rgb_brightness >= 100) {
        // No changes
        return;
    }

    config.rgb_brightness += 10;
    if (config.rgb_brightness > 100) {
        config.rgb_brightness = 100;
    }

    api_set_config(config);
}

void handle_decrease_brightness(rgb_config config) {
    if (config.rgb_brightness <= 0) {
        // No changes
        return;
    }

    config.rgb_brightness -= 10;
    if (config.rgb_brightness < 0) {
        config.rgb_brightness = 0;
    }

    api_set_config(config);
}
