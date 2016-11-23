#include "base64.h"
#include <stdio.h> // printf()
#include <stdlib.h> // free()
#include <string.h> // strlen()

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_STRING(expect, actual, alength) EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength) == 0, expect, actual, "%s")

#define TEST_ENCODE(expect, string)\
    do {\
        char* result = btoa((unsigned char*)&string);\
        EXPECT_EQ_STRING(expect, result, strlen(result));\
        free(result);\
    } while(0)

#define TEST_DECODE(expect, string)\
    do {\
        char* result = atob((const char *)&string);\
        EXPECT_EQ_STRING(expect, result, strlen(result));\
        free(result);\
    } while(0)

static void test_btoa() {
    TEST_ENCODE("YQ==", "a");
    TEST_ENCODE("YWI=", "ab");
    TEST_ENCODE("YWJj", "abc");
    TEST_ENCODE("w7fDtw==", "÷÷");
    TEST_ENCODE("w7c=", "÷");
    TEST_ENCODE("w7fDt8O3", "÷÷÷");
    TEST_ENCODE("5pmL5Lilw7dhYmNk44CK5aaC5L2V5Y+Y5b6X5pyJ5oCd5oOz44CL5Ye654mI5LqG77yB", "晋严÷abcd《如何变得有思想》出版了！");
}

static void test_atob() {
    TEST_DECODE("a", "YQ==");
    TEST_DECODE("ab", "YWI=");
    TEST_DECODE("abc", "YWJj");
    TEST_DECODE("÷", "w7c=");
    TEST_DECODE("÷÷", "w7fDtw==");
    TEST_DECODE("÷÷÷", "w7fDt8O3");
    TEST_DECODE("晋严÷abcd《如何变得有思想》出版了！", "5pmL5Lilw7dhYmNk44CK5aaC5L2V5Y+Y5b6X5pyJ5oCd5oOz44CL5Ye654mI5LqG77yB");
}

int main() {
    test_atob();
    test_btoa();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}
