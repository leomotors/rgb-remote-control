#include "post.h"

#include <stdio.h>
#include <stdlib.h>

#include "http.h"
#include "models.h"

#define SET_CONFIG_URL "http://localhost:34001/api/v1.0/set-config"

void api_set_config(rgb_config config) {
    char* body = (char*)malloc(16384 * sizeof(char));

    char* serialized = serialize_config(config);

    sprintf(body, "{\"data\":{\"auto\":%s}}", serialized);
    free(serialized);

    http_post_json(SET_CONFIG_URL, body);
    free(body);
}
