#include "test.h"

// succeeding tests
test(strlen_works, {
    char phrase[] = "hey apple";
    int length = strlen(phrase);
    expect(length == 9);
})

test(quick_maths, {
    expect(1 + 1 == 2);
})

test(even_quicker_maths, {
    expect(2 == 2);
})

// failing test
test(apple_is_equals_to_banana, {
    char word[] = "apple";
    expect(strcmp(word, "banana") == 0);
})

TEST_SUITE
