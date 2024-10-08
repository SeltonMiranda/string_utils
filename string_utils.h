#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define DSA static inline
#define INITIAL_CAPACITY 1024

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} string_t;

DSA string_t *string_create(const char *initial);
DSA void string_free(string_t *str);
DSA void string_append_char(string_t *str, char c);
DSA void string_append(string_t* dest, const string_t *src);
DSA int string_find(const string_t *str, const string_t *substr);
DSA int string_find_literal(const string_t* str, const char* literal);
DSA string_t** string_tokenize(const string_t* str, const char* delimiter, size_t* token_count);
DSA string_t* string_read_file(const char* filename);
DSA int string_save_to_file(const string_t* str, const char* filename, const char* mode);
DSA void string_print(const string_t* str);
DSA void string_trim(string_t* str);
DSA void string_trim_left(string_t* str);
DSA void string_trim_right(string_t* str);
DSA int string_compare(const string_t* str1, const string_t* str2);

#ifdef ST_IMPLEMENTATION

DSA string_t *string_create(const char *initial) {
    string_t *str = (string_t *)malloc(sizeof(string_t));
    if (!str) return NULL;

    if (initial) {
        str->length = strlen(initial);
        str->capacity = str->length + INITIAL_CAPACITY;
        str->data = (char *)malloc(str->capacity);
        if (!str->data) {
            free(str);
            return NULL;
        }
        strcpy(str->data, initial);
        return str;
    }
    
    str->length = 0;
    str->capacity = INITIAL_CAPACITY;
    str->data = (char *)malloc(str->capacity);
    if (!str->data) {
        free(str);
        return NULL;
    }
    str->data[0] = '\0';
    return str;
}

DSA void string_free(string_t *str) {
    free(str->data);
    free(str);
}

DSA void string_append_char(string_t *str, char c) {
    if (str->length + 1 >= str->capacity) {
        str->capacity *= 2;
        str->data = (char *)realloc(str->data, str->capacity);
    }

    str->data[str->length++] = c;
    str->data[str->length] = '\0';
}

DSA void string_append(string_t *dest, const string_t *src) {
    if (!src || src->length == 0) return;

    if (dest->length + src->length >= dest->capacity) {
        while (dest->length + src->length >= dest->capacity)
            dest->capacity *= 2;
        dest->data = (char *)realloc(dest->data, dest->capacity);
    }

    strcpy(dest->data + dest->length, src->data);
    dest->length += src->length;
}

DSA int string_find(const string_t *str, const string_t *substr) {
    if (!substr || substr->length == 0) return -1;

    char *pos = strstr(str->data, substr->data);
    if (pos) {
        return (int)(pos - str->data);
    }
    return -1;
}

DSA int string_find_literal(const string_t* str, const char* literal) {
    if (!literal || literal[0] == '\0') return -1;
    char *pos = strstr(str->data, literal);
    if (pos) {
        return (int)(pos - str->data);
    }
    return -1;
}

DSA string_t** string_tokenize(const string_t* str, const char* delimiter, size_t* token_count) {
    if (!delimiter || delimiter[0] == '\0') return NULL;

    char *temp = strdup(str->data);
    char *token = strtok(temp, delimiter);

    string_t **tokens = NULL;
    *token_count = 0;

    while (token) {
        tokens = realloc(tokens, sizeof(string_t *) * (*token_count + 1));
        tokens[*token_count] = string_create(token);
        (*token_count)++;
        token = strtok(NULL, delimiter);
    }
    free(temp);
    return tokens;
}

DSA string_t* string_read_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    string_t *str = string_create(NULL);
    if (!str) {
        fclose(file);
        return NULL;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        if (str->length + len >= str->capacity) {
            while (str->length + len >= str->capacity)
                str->capacity *= 2;
            str->data = (char *)realloc(str->data, str->capacity);
        }
        strcpy(str->data + str->length, buffer);
        str->length += len;
    }
    fclose(file);
    return str;
}

DSA int string_save_to_file(const string_t* str, const char* filename, const char* mode) {
    FILE *file = fopen(filename, mode);
    if (!file) return 0;

    size_t written = fwrite(str->data, sizeof(char), str->length, file);
    fclose(file);
    return (written == str->length) ? 0 : 1;
}

DSA void string_print(const string_t* str) {
    if (str && str->data) {
        printf("%s", str->data);
    }
}

DSA void string_trim(string_t* str) {
    string_trim_left(str);
    string_trim_right(str);
}

void string_trim_left(string_t* str) {
    size_t start = 0;
    while (start < str->length && isspace((unsigned char)str->data[start]))
        start++;

    if (start > 0) {
        memmove(str->data, str->data + start, str->length - start + 1);
        str->length -= start;
    }
}

void string_trim_right(string_t* str) {
    while (str->length > 0 && isspace((unsigned char)str->data[str->length - 1]))
        str->length--;
    str->data[str->length] = '\0';
}

DSA int string_compare(const string_t* str1, const string_t* str2) {
    if (str1->length != str2->length) {
        return 0;
    }
    return strcmp(str1->data, str2->data) == 0 ? 1 : 0;
}

#endif // ST_IMPLEMENTATION

#endif // STRING_UTILS_H
