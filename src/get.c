#include "get.h"

#include <stdio.h>

#include "http.h"
#include "models.h"

#ifndef BASE_URL
#define BASE_URL "http://localhost:34001"
#endif
#define GET_CONFIG_URL BASE_URL "/api/v1.0/get-config"

/**
 * Get the configuration from the API.
 *
 * Don't forget to FREE rgb_config!
 */
rgb_config api_get_config() {
    struct json_object* object = http_get(GET_CONFIG_URL);

    if (object == NULL) {
        fprintf(stderr, "Error getting config from API\n");
        return (rgb_config){0};
    }

    rgb_config config = parse_config(object);

    return config;
}
