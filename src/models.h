#pragma once

#include <json-c/json.h>
#include <stdbool.h>

/*
 * "gpio_fan_mode": 0,
 * "gpio_fan_pin": 6,
 * "rgb_brightness": 100,
 * "rgb_color": "ff0000",
 * "rgb_enable": true,
 * "rgb_led_count": 4,
 * "rgb_speed": 69,
 * "rgb_style": "rainbow",
 * "temperature_unit": "C"
 */

typedef struct {
    int gpio_fan_mode;
    int gpio_fan_pin;
    int rgb_brightness;
    char* rgb_color;
    bool rgb_enable;
    int rgb_led_count;
    int rgb_speed;
    char* rgb_style;
    char* temperature_unit;
} rgb_config;

rgb_config parse_config(struct json_object* object);
void free_rgb_config(rgb_config config);

char* serialize_config(rgb_config config);
