#include "base64.h"
#include <string.h> // strlen()
#include <stdlib.h> // realloc()

static const char *Base64Hash = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


char* btoa(const char* s) {
    char *result = malloc(sizeof(char));
    int i = 0, mod, result_len = 1;
    size_t len = strlen(s);

    while(i < len) {
        mod = i % 3;
        switch (mod) {
            case 0:
                result_len++;
                result = realloc(result, result_len * sizeof(char));
                result[result_len-2] = Base64Hash[(unsigned char)s[i] >> 2];
                break;
            case 1:
                result_len++;
                result = realloc(result, result_len * sizeof(char));
                result[result_len-2] = Base64Hash[((unsigned char)s[i-1] & 3) << 4 | (unsigned char)s[i] >> 4];
                break;
            case 2:
                result_len += 2;
                result = realloc(result, result_len * sizeof(char));
                result[result_len-3] = Base64Hash[((unsigned char)s[i-1] & 15) << 2 | ((unsigned char)s[i] >> 6)];
                result[result_len-2] = Base64Hash[(unsigned char)s[i] & 63];
                break;
        }
        i++;
    }

    if (mod == 0) {
        result_len += 3;
        result = realloc(result, result_len * sizeof(char));
        result[result_len - 4] = Base64Hash[((unsigned char)s[i-1] & 3) << 4];
        result[result_len - 2] = result[result_len - 3] = '=';
    } else if (mod == 1) {
        result_len += 2;
        result = realloc(result, result_len * sizeof(char));
        result[result_len - 3] = Base64Hash[((unsigned char)s[i-1] & 15) << 2];
        result[result_len - 2] = '=';
    }

    return result;
}
