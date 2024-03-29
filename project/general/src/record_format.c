#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "load_database.h"
#include "utils.h"

#define LENGTH_STRING_FORMAT 10

format_t *create_set_format() {
    format_t *format = calloc(1, sizeof(format_t));
    if (!format) {
        fprintf(stderr, ERR_ALOC_M);
        return NULL;
    }

    format->name = create_format(L_NAME, LENGTH_STRING_FORMAT);
    if (!format->name) {
        free(format);
        return NULL;
    }

    format->surname = create_format(L_SURNAME, LENGTH_STRING_FORMAT);
    if (!format->surname) {
        fprintf(stderr, ERR_ALOC_M);

        free_set_format(format);
        return NULL;
    }

    format->gender = create_format(L_GENDER, LENGTH_STRING_FORMAT);
    if (!format->gender) {
        fprintf(stderr, ERR_ALOC_M);

        free_set_format(format);
        return NULL;
    }

    format->age = create_format(L_AGE, LENGTH_STRING_FORMAT);
    if (!format->age) {
        fprintf(stderr, ERR_ALOC_M);

        free_set_format(format);
        return NULL;
    }

    format->salary = create_format(L_SALARY, LENGTH_STRING_FORMAT);
    if (!format->salary) {
        fprintf(stderr, ERR_ALOC_M);

        free_set_format(format);
        return NULL;
    }

    format->position = create_format(L_POSITION, LENGTH_STRING_FORMAT);
    if (!format->position) {
        fprintf(stderr, ERR_ALOC_M);

        free_set_format(format);
        return NULL;
    }

    format->experience = create_format(L_EXPERIENCE, LENGTH_STRING_FORMAT);
    if (!format->experience) {
        fprintf(stderr, ERR_ALOC_M);

        free_set_format(format);
        return NULL;
    }

    return format;
}

int free_set_format(format_t *format) {
    free(format->name);
    free(format->surname);
    free(format->gender);
    free(format->age);
    free(format->salary);
    free(format->position);
    free(format->experience);

    free(format);

    return SUCCESS;
}
