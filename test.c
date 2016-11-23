#include "base64.h"
#include <stdio.h> // prinf()
#include <stdlib.h> // free()
#include <string.h> // strlen()

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

static void test_btoa() {
    char* result;
    const char* s1 = "÷";
    result = btoa(s1);
    printf("%s\n", result);


    /*
    const char* s2 = "ab";
    result = btoa(s2);
    printf("%s\n", result);

    const char* s3 = "abc";
    result = btoa(s3);
    printf("%s\n", result);

    const char* s4 = "abcd";
    result = btoa(s4);
    printf("%s\n", result);


    const char* test = "÷";
    printf("%zu\n", strlen(test));
    */

    const char* s2 = "晋严÷abcd";
    result = btoa(s2);
    printf("%s\n", result);

    free(result);
}

static void test_atob() {

}

int main() {
    test_btoa();
    test_atob();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}
