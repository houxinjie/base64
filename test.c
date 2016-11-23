#include "base64.h"
#include <stdio.h> // prinf()
#include <stdlib.h> // free()

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

static void test_btoa() {
    char* result;
    const char* s1 = "÷";
    printf("%s\n", s1);
    result = btoa((unsigned char*)s1);
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

    const char* s2 = "晋严÷abcd《如何变得有思想》出版了！";
    printf("%s\n", s2);
    result = btoa((unsigned char*)s2);
    printf("%s\n", result);

    free(result);
}

static void test_atob() {
    char* result;
    char* s = "5pmL5Lilw7dhYmNk44CK5aaC5L2V5Y+Y5b6X5pyJ5oCd5oOz44CL5Ye654mI5LqG77yB";
    result = atob(s);
    printf("%s\n", result);
    free(result);
}

int main() {
    test_btoa();
    test_atob();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}
