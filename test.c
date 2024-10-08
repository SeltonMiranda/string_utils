#include <stdio.h>
#define ST_IMPLEMENTATION
#include "string_utils.h"

#define TEST_CASE(name) void name()
#define RUN_TEST(name) \
    do { \
        printf("Running %s...\n", #name); \
        name(); \
    } while (0)

#define ASSERT_EQ(expected, actual) do { \
    if ((expected) != (actual)) { \
        printf("Assertion failed: %s == %s at %s:%d\n", \
#expected, #actual, __FILE__, __LINE__); \
        return; \
    } \
} while (0);

#define ASSERT_STR_EQ(expected, actual) do { \
    if (strcmp(expected, actual) != 0) { \
        printf("Assertion failed: %s == %s at %s:%d\n", \
#expected, #actual, __FILE__, __LINE__); \
        return; \
    } \
} while (0);

TEST_CASE(test_string_create) {
    string_t *str = string_create("Hello");
    ASSERT_STR_EQ("Hello", str->data);
    ASSERT_EQ(5, str->length);
    ASSERT_EQ(INITIAL_CAPACITY + str->length, str->capacity);
    string_free(str);
}

TEST_CASE(test_string_append) {
    string_t* str1 = string_create("Hello");
    string_t* str2 = string_create(", World!");
    string_append(str1, str2);
    ASSERT_STR_EQ("Hello, World!", str1->data);
    ASSERT_EQ(13, str1->length);
    string_free(str1);
    string_free(str2);
}

TEST_CASE(test_string_find) {
    string_t* str = string_create("Hello, World!");
    string_t* substr = string_create("World");
    ASSERT_EQ(7, string_find(str, substr));
    string_free(str);
    string_free(substr);
}

TEST_CASE(test_string_replace) {
    string_t *str = string_create("Hello, World!");
    const char *old_sub = "World";
    const char *new_sub = "Universe";

    string_t *result = string_replace(str, old_sub, new_sub);
    ASSERT_STR_EQ("Hello, Universe!", result->data);

    string_free(str);
    string_free(result);  // No need to free old_sub and new_sub as they are literals
}

int main() {
    RUN_TEST(test_string_create);
    RUN_TEST(test_string_append);
    RUN_TEST(test_string_find);
    RUN_TEST(test_string_replace);
    // I will implement the tests lefting, now I'm too tired
    return 0;
}
