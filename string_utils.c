#include "string_utils.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>

String str_create(const char* src) {
    String str;

    if (src != NULL) {
        str.length = strlen(src);
        str.cap = str.length + 1;
        str.data = (char *)malloc(str.cap * sizeof(char));
        if (str.data) strcpy(str.data, src);
    } else {
        str.length = 0;
        str.cap = 1;
        str.data = NULL;
    }
    
    return str;
}

void str_free(String* str) {
    if (str->data) {
        free(str->data);
        str->data = NULL;
    }
    str->length = 0;
    str->cap = 0;
}

void str_append(String* str, const char* suffix) {
    size_t suffix_len = strlen(suffix);
    size_t new_len = str->length + suffix_len;

    if (new_len + 1 > str->cap) {
        str->cap = new_len + 1;
        str->data = (char *)realloc(str->data, str->cap * sizeof(char));
    }

    if (str->data) {
        strcat(str->data, suffix);
        str->length = new_len;
    }
}

void str_append_char(String* str, char c) {
    if (str->length + 1 >= str->cap) {
        str->cap = str->cap * 2 + 1;
        str->data = (char *)realloc(str->data, str->cap * sizeof(char));
    }

    if (str->data) {
        str->data[str->length] = c;
        str->length++;
        str->data[str->length] = '\0';
    }
}

void str_clear(String* str) {
    str->length = 0;
    if (str->data) {
        str->data[0] = '\0';
    }
}

void str_copy(String* dest, const String* src) {
    if (src->length + 1 > dest->cap) {
        dest->cap = src->length + 1;
        dest->data = (char*)realloc(dest->data, dest->cap * sizeof(char));
    }

    if (dest->data) {
        strcpy(dest->data, src->data);
        dest->length = src->length;
    }
}

void str_resize(String* str, size_t new_size) {
    if (new_size >= str->cap) {
        str->cap = new_size + 1;
        str->data = (char*)realloc(str->data, str->cap * sizeof(char));
    }

    if (str->data) {
        str->length = new_size;
        str->data[str->length] = '\0';
    }
}

String* str_split(const char* str, const char* delim, size_t* token_count) {
    char* temp = strdup(str);
    char* token = strtok(temp, delim);
    size_t count = 0;

    while (token != NULL) {
        count++;
        token = strtok(NULL, delim);
    }

    String* tokens = (String*)malloc(count * sizeof(String));
    if (!tokens) {
        free(temp);
        return NULL;
    }

    strcpy(temp, str);
    token = strtok(temp, delim);
    size_t i = 0;
    while (token != NULL) {
        tokens[i] = str_create(token);
        token = strtok(NULL, delim);
        i++;
    }

    *token_count = count;
    free(temp);
    return tokens;
}

void str_trim_left(String* str) {
    size_t i = 0;
    while (isspace((unsigned char)str->data[i])) {
        i++;
    }
    if (i > 0) {
        str->length -= i;
        memmove(str->data, str->data + i, str->length + 1);
    }
}

void str_trim_right(String* str) {
    while (str->length > 0 && isspace((unsigned char)str->data[str->length - 1])) {
        str->length--;
    }

    str->data[str->length] = '\0';
}

void str_trim(String* str) {
    str_trim_right(str);
    str_trim_left(str);
    return;
}

int str_starts_with(const String* str, const char* prefix) {
    size_t prefix_len = strlen(prefix);
    if (prefix_len > str->length) {
        return 0;
    }
    return strncmp(str->data, prefix, prefix_len) == 0;
}

int str_ends_with(const String* str, const char* suffix) {
    size_t suffix_len = strlen(suffix);
    if (suffix_len > str->length) {
        return 0;
    }
    return strncmp(str->data + str->length - suffix_len, suffix, suffix_len) == 0;
}

void str_add_prefix(String* str, const char* prefix) {
    size_t prefix_len = strlen(prefix);
    size_t new_len = str->length + prefix_len;

    if (new_len + 1 > str->cap) {
        str->cap = new_len + 1;
        str->data = (char*)realloc(str->data, str->cap);
    }

    if (str->data) {
        memmove(str->data + prefix_len, str->data, str->length - 1);
        memcpy(str->data, prefix, prefix_len);
        str->length = new_len;
    }
}

void str_add_suffix(String* str, const char* suffix) {
    str_append(str, suffix);
}

String str_join(const char** strings, size_t count, const char* delimiter) {
    String result = SU_NULL;  

    if (count == 0) {
        result.data = strdup(""); 
        if (result.data) {
            result.length = 0;
            result.cap = 1;
        }
        return result;
    }

    size_t delimiter_len = strlen(delimiter);
    size_t total_len = 0;

    for (size_t i = 0; i < count; i++) {
        total_len += strlen(strings[i]);
        if (i < count - 1) {
            total_len += delimiter_len; 
        }
    }

    result.data = (char*)malloc((total_len + 1) * sizeof(char));
    if (!result.data) {
        return result; 
    }

    result.data[0] = '\0';  
    result.length = total_len;
    result.cap = total_len + 1;

    for (size_t i = 0; i < count; i++) {
        strcat(result.data, strings[i]);
        if (i < count - 1) {
            strcat(result.data, delimiter);
        }
    }
    return result;  
}

ssize_t str_indexOf(const String* str, const char* substring) {
    if (str == NULL || str->data == NULL || substring == NULL) {
        return -1;
    }

    char* pos = strstr(str->data, substring);
    if (pos == NULL) {
        return -1;
    }
    return pos - str->data;
}

String str_format(const char* format, ...) {
    String result  = SU_NULL; 

    if (format == NULL) {
        return result;
    }

    va_list args;
    va_start(args, format);
    size_t needed = vsnprintf(NULL, 0, format, args);
    va_end(args);

    result.data = (char*)malloc((needed + 1) * sizeof(char));
    if (result.data == NULL) {
        return result;
    }

    result.cap = needed + 1;
    va_start(args, format);
    vsnprintf(result.data, needed + 1, format, args);
    va_end(args);

    result.length = needed;

    return result;
}

char str_char_at(String* str, size_t index) {
    if (index >= str->length || str->data == NULL)
        return '\0';
    return str->data[index];
}

