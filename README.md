# cUnit

![preview](preview.gif)

A simple test lib to build expressive tests. :muscle:

## Why?

Just to have fun exploiting the most out of macros :laughing:

## Usage

This is how a *test suite* looks like. 

```c
#include "test.h"

// failing test
test(apple_is_equals_to_banana, {
    char word[] = "apple";
    expect(strcmp(word, "banana") == 0);
})

// succeeding test
test(strlen_works, {
    char phrase[] = "hey apple";
    int length = strlen(phrase);
    expect(length == 9);
})

TEST_SUITE
```

Each suite consists in a group of tests which are ran sequentially, 
in the same order they were declared. 

Each test is declared inside a test block, which receives as arguments 
a **name** (in [snake_case](https://en.wikipedia.org/wiki/Snake_case)) and 
a fancy looking **function** body.

## What is this `TEST_SUITE` thing?

Well, it's just helper to generate a `main()` for you, but it requires 
the flags `-rdynamic -ldl` to be set at compile time.

But, if you can't have it, you may write your own. 
The structure looks like this:

```c
int main() {
    test_runner(apple_is_equals_to_banana);
    test_runner(strlen_works);
    return test_exit_code;
}
```

> We set up test runners and exit code. If any test fail, 
> the program closes with either `EXIT_FAILURE` (1) or `EXIT_SUCCESS` (0) code.

It's simple enought that you can write a script to set it up for you, 
if you wish.

## That's all folks

Hope you find it interesting as I did. Definitely had some fun 
messing up with macros, you should look it up too.

Also, what are you waiting for? Go have some fun with testing. 🚀
