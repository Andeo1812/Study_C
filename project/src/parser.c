#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <stdio.h>

#include <parser.h>

char *search_begin_header(char *source, char const *key) {
    char *ptr_header = strcasestr(source, key);
    if (!ptr_header) {
        return NULL;
    }

    size_t length_key = strlen(key);

    while (true) {
        if (ptr_header == source || *(ptr_header - 1) == '\n') {
            return ptr_header + length_key + skip_space(ptr_header + length_key);
        } else {
            ptr_header++;
            ptr_header = strcasestr(ptr_header, key);
        }
    }
}

char *search_end_header(char *start) {
    char *pos = start;

    while (true) {
        char *end = strchr(pos, '\r');
        if (!end) {
            end = strchr(pos, '\n');
        }

        if (!end) {
            return NULL;
        }

        pos = end;

        while (*end == '\n' || *end == '\r') {
            end++;
        }

        if (!check_str(end + 1)) {
            break;
        } else {
            pos = end + 1;
        }
    }

    return pos;
}

char *parser_key_header(char *source, char const *key) {
    char *pos = search_begin_header(source, key);
    char *start = pos;

    if (!pos) {
        return strdup("");
    }

    pos = search_end_header(start);

    char *value = get_value_header(start, pos);

    return value;
}

size_t parser_key_parts(char *source) {
    size_t res = 1;

    char *pos_type = search_begin_header(source, TYPE);
    if (!pos_type) {
        return res;
    }

    char value[MAX_LENGTH_COMPARE];

    snprintf(value, sizeof(value), "%s", pos_type);

    char *pos_mul = strcasestr(value, MULTIPART);
    if (!pos_mul) {
        return res;
    }

    char *pos = strcasestr(pos_mul, BOUNDARY);
    if (!pos || isalpha(*(pos - 1))) {
        return res;
    }

    pos += strlen(BOUNDARY);

    char *key_boundary = get_boundary_key(pos);

    pos = strstr(source, key_boundary);

    while (pos) {
        pos++;
        pos = strstr(pos, key_boundary);
        if (pos && isspace(pos[strlen(key_boundary)])) {
            res++;
        }
    }

    free(key_boundary);

    return res - 1;
}

eml_t *parser(char *source) {
    eml_t *eml = calloc(1, sizeof(eml_t));
    if (!eml) {
        return NULL;
    }

    eml->source = parser_key_header(source, FROM);
    eml->target = parser_key_header(source, TO);
    eml->date = parser_key_header(source, DATE);
    eml->parts = parser_key_parts(source);

    return eml;
}
