#include "models.h"

#include <json-c/json.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

rgb_config parse_config(struct json_object *object) {
    struct json_object *data = json_object_object_get(object, "data");

    if (data == NULL) {
        fprintf(stderr, "Error parsing JSON: data field not found\n");
        return (rgb_config){0};
    }

    struct json_object *config = json_object_object_get(data, "auto");

    if (config == NULL) {
        fprintf(stderr, "Error parsing JSON: config field not found\n");
        return (rgb_config){0};
    }

    rgb_config rgb = {
        .gpio_fan_mode = json_object_get_int(
            json_object_object_get(config, "gpio_fan_mode")),
        .gpio_fan_pin =
            json_object_get_int(json_object_object_get(config, "gpio_fan_pin")),
        .rgb_brightness = json_object_get_int(
            json_object_object_get(config, "rgb_brightness")),
        .rgb_color = duplicate_const_str(json_object_get_string(
            json_object_object_get(config, "rgb_color"))),
        .rgb_enable = json_object_get_boolean(
            json_object_object_get(config, "rgb_enable")),
        .rgb_led_count = json_object_get_int(
            json_object_object_get(config, "rgb_led_count")),
        .rgb_speed =
            json_object_get_int(json_object_object_get(config, "rgb_speed")),
        .rgb_style = duplicate_const_str(json_object_get_string(
            json_object_object_get(config, "rgb_style"))),
        .temperature_unit = duplicate_const_str(json_object_get_string(
            json_object_object_get(config, "temperature_unit"))),
    };

    return rgb;
}

void free_rgb_config(rgb_config config) {
    free(config.rgb_color);
    free(config.rgb_style);
    free(config.temperature_unit);
}
