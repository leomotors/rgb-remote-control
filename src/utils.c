#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *duplicate_const_str(const char *src) {
    char *dest = (char *)malloc(strlen(src) + 1);
    if (dest == NULL) {
        return NULL;
    }

    strcpy(dest, src);
    return dest;
}

/**
 * Don't forget to FREE the string
 */
char *get_time_string() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char *time_str = (char *)malloc(128);

    sprintf(time_str, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900,
            tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    return time_str;
}
