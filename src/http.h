#pragma once

#include <json-c/json.h>

struct json_object *http_get(const char *url);
void http_post_json(const char *url, const char *json_data);
