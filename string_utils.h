#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdio.h>
#include <stdint.h>

// This small library defines a custom string structure with memory management.
typedef struct String {
    char *data;    // Pointer to the array of characters (actual string data)
    size_t length; // Length of the string (excludes '\0')
    size_t cap;    // Total allocated capacity for the string (includes '\0')
} String;

// Macros to simplify string creation and usage
#define SU_NULL str_create(NULL)  // Creates an empty string
#define SU(src) str_create(src)   // Creates a string from a literal

#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof((arr)[0]))
#define STR_JOIN(arr, delimiter) str_join(arr, ARRAY_COUNT(arr), delimiter)


/*
 * Creates a String object from a C-string (const char*).
 * Allocates memory based on the source string and copies the content.
 * @param src The source C-string.
 * @returns a String object.
 */
String str_create(const char* src);

/*
 * Frees the memory allocated for the String object's data.
 * @param str Pointer to the String object to be freed.
 */
void str_free(String* str);

/*
 * Appends a C-string (const char*) to the existing String object.
 * Reallocates memory if necessary.
 * @param str Pointer to the String object to which the suffix will be appended.
 * @param suffix The C-string to append.
 */
void str_append(String* str, const char* suffix);

/*
 * Appends a single character to the end of the String object.
 * Reallocates memory if needed.
 * @param str Pointer to the String object.
 * @param c The character to append.
 */
void str_append_char(String* str, char c);

/*
 * Clears the content of the String object by setting its length to 0.
 * Does not free the allocated memory.
 * @param str Pointer to the String object to clear.
 */
void str_clear(String* str);

/*
 * Copies the content of one String object (src) to another (dest).
 * Resizes the destination String if necessary.
 * @param dest Pointer to the destination String.
 * @param src Pointer to the source String.
 */
void str_copy(String* dest, const String* src);

/*
 * Resizes the capacity of the String object to the new size.
 * This can either grow or shrink the allocated memory.
 * @param str Pointer to the String object.
 * @param new_size The new size to which the capacity should be resized.
 */
void str_resize(String* str, size_t new_size);

/*
 * Removes leading left whitespace from the String object.
 * Modifies the string in place.
 * @param str Pointer to the String object.
 */
void str_trim_left(String* str);

/*
 * Removes trailing right whitespace from the String object.
 * Modifies the string in place.
 * @param str Pointer to the String object.
 */
void str_trim_right(String* str);

/**
 * Removes both right and left leading and trailing whitespace from the String object.
 * Modifies the string in place.
 * @param str Pointer to the String object.
 */
void str_trim(String* str);

/*
 * Checks if the String object starts with a specific prefix (C-string).
 * @param str Pointer to the String object.
 * @param prefix The C-string to check as the prefix.
 * @return 1 if the string starts with the given prefix, 0 otherwise.
 */
int str_starts_with(const String* str, const char* prefix);

/*
 * Checks if the String object ends with a specific suffix (C-string).
 * @param str Pointer to the String object.
 * @param suffix The C-string to check as the suffix.
 * @return 1 if the string ends with the given suffix, 0 otherwise.
 */
int str_ends_with(const String* str, const char* suffix);

/*
 * Adds a prefix (C-string) to the beginning of the String object.
 * Reallocates memory if necessary.
 * @param str Pointer to the String object.
 * @param prefix The C-string to add as a prefix.
 */
void str_add_prefix(String* str, const char* prefix);

/*
 * Adds a suffix (C-string) to the end of the String object.
 * Reallocates memory if necessary.
 * @param str Pointer to the String object.
 * @param suffix The C-string to add as a suffix.
 */
void str_add_suffix(String* str, const char* suffix);

/*
 * Finds the first occurrence of a substring (C-string) in the String object.
 * @param str Pointer to the String object.
 * @param substring The C-string to search for.
 * @return The index of the first occurrence, or -1 if not found.
 */
ssize_t str_indexOf(const String* str, const char* substring);

/*
 * Splits the String object into tokens based on the provided delimiter.
 * Allocates memory for each token and returns an array of String objects.
 * @param str The source C-string to split.
 * @param delim The delimiter to use for splitting.
 * @param token_count Pointer to store the number of tokens found.
 * @return An array of String objects representing the tokens.
 */
String* str_split(const char* str, const char* delim, size_t* token_count);

/*
 * Joins multiple C-strings into a single String object, using a delimiter.
 * Allocates memory for the resulting String object.
 * @param strings An array of C-strings to join.
 * @param count The number of strings in the array.
 * @param delimiter The delimiter to insert between the strings.
 * @return A new String object with the joined content.
 */
String str_join(const char** strings, size_t count, const char* delimiter);

/*
 * Formats a string similarly to printf, but returns the result as a String object.
 * Supports variable argument lists.
 * @param format The format string (printf-style).
 * @return A new String object containing the formatted output.
 */
String str_format(const char* format, ...);

/*
 * Retrieves the character at the specified index from the String object.
 * Performs bounds checking and returns '\0' if the index is out of range.
 * @param str Pointer to the String object.
 * @param index The index of the character to retrieve.
 * @return The character at the specified index, or '\0' if out of bounds.
 */
char str_char_at(String* str, size_t index);

#endif // STRING_UTILS_H
