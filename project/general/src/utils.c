#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

#define MAX_LENGTH_BUF 80

#define LENGTH_STRING_FORMAT 10

char *create_str(const char *source) {
    size_t len = strlen(source);

    char *tmp = calloc(len + 1, sizeof(char));
    if (!tmp) {
        fprintf(stderr, ERR_ALOC_M);
        return NULL;
    }

    tmp = strncpy(tmp, source, len);

    tmp[len] = '\0';

    return tmp;
}

char *create_format(const size_t size_str, const size_t size_format) {
    char *format = calloc(size_format, sizeof(char));
    if (!format) {
        fprintf(stderr, ERR_ALOC_M);
        return NULL;
    }

    snprintf(format, size_format, "%%%zus", size_str - 1);

    return format;
}
