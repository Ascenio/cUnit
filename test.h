#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <dlfcn.h>

#define GREEN "\033[92m"
#define RED "\033[91m"
#define CLEAR "\033[0m"

int test_exit_code = EXIT_SUCCESS;

#define CONCAT_HELPER(x, y) x##y
#define CONCAT(x, y) CONCAT_HELPER(x, y)

#define test(function_name, function_body)   \
const char *function_name();                 \
                                             \
void CONCAT(test_internal_, __COUNTER__)() { \
    test_runner(function_name);              \
}                                            \
                                             \
const char *function_name() {                \
    function_body                            \
    return NULL;                             \
}

#define test_runner(function)                                    \
do {                                                             \
    const char *error = function();                              \
    if (error) {                                                 \
        test_exit_code = EXIT_FAILURE;                           \
        printf(RED "☓ %s failed: %s\n" CLEAR, #function, error); \
    }                                                            \
    else {                                                       \
        printf(GREEN "✔ %s\n" CLEAR, #function);                 \
    }                                                            \
} while (0)

#define expect(expr)  \
do {                  \
    if (!(expr)) {    \
        return #expr; \
    }                 \
} while (0)

typedef void (*voidcallback)();

void test_suite_helper(char* test_name) {
    void *handle = dlopen(NULL, RTLD_NOW);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(EXIT_FAILURE);
    }
    voidcallback function = (voidcallback) dlsym(handle, test_name);
    char* error = dlerror();
    if (error) {
        fputs(error, stderr);
        exit(EXIT_FAILURE);
    }
    function();
    dlclose(handle);
}

#define TEST_SUITE                                        \
int main() {                                              \
    int tests_count = __COUNTER__;                        \
    for (int i = 0; i < tests_count; i++) {               \
        char test_name[100] = "test_internal_";           \
        char test_number_string[3];                       \
        sprintf(test_number_string, "%d", i);             \
        strncat(test_name, test_number_string, 100 - 14); \
        test_suite_helper(test_name);                     \
    }                                                     \
    return test_exit_code;                                \
}
