#include "http.h"

#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "models.h"
#include "utils.h"

#define USER_AGENT "rgb-remote-control/1.0"

// Structure to hold the response data
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Callback function to write data into the MemoryStruct
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb,
                                  void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        // Out of memory!
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

/**
 * Perform a GET request to the given URL, returns json_object ptr as body.
 *
 * Don't forget to FREE!
 */
struct json_object *http_get(const char *url) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = (char *)malloc(1);  // Allocate initial memory
    chunk.size = 0;                    // No data at this point

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    struct json_object *return_value = NULL;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        } else {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

            char *current_time_str = get_time_string();
            printf("[%s] GET %ld %s:\n%s\n", current_time_str, http_code, url,
                   chunk.memory);
            free(current_time_str);

            // Parse JSON data
            return_value = json_tokener_parse(chunk.memory);
        }

        curl_easy_cleanup(curl);
    }

    free(chunk.memory);
    curl_global_cleanup();

    return return_value;
}
