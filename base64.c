#include "base64.h"
#include <string.h> // strlen()
#include <stdlib.h> // malloc() realloc()

static const char *encode_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char *decode_table = NULL;

void build_decode_table() {
    decode_table = malloc(128 * sizeof(unsigned char));
    for (int i = 0; i < 64; i++) {
        decode_table[(unsigned char) encode_table[i]] = i;
    }
}


char* btoa(const unsigned char* s) {
    char *result = malloc(sizeof(char));
    int i = 0, mod, result_len = 1;
    size_t len = strlen((char*)s);

    while(i < len) {
        mod = i % 3;
        switch (mod) {
            case 0:
                result_len++;
                result = realloc(result, result_len * sizeof(char));
                result[result_len-2] = encode_table[s[i] >> 2];
                break;
            case 1:
                result_len++;
                result = realloc(result, result_len * sizeof(char));
                result[result_len-2] = encode_table[(s[i-1] & 3) << 4 | s[i] >> 4];
                break;
            case 2:
                result_len += 2;
                result = realloc(result, result_len * sizeof(char));
                result[result_len-3] = encode_table[(s[i-1] & 15) << 2 | (s[i] >> 6)];
                result[result_len-2] = encode_table[s[i] & 63];
                break;
        }
        i++;
    }

    if (mod == 0) {
        result_len += 3;
        result = realloc(result, result_len * sizeof(char));
        result[result_len - 4] = encode_table[(s[i-1] & 3) << 4];
        result[result_len - 3] = result[result_len - 2] = '=';
    } else if (mod == 1) {
        result_len += 2;
        result = realloc(result, result_len * sizeof(char));
        result[result_len - 3] = encode_table[(s[i-1] & 15) << 2];
        result[result_len - 2] = '=';
    }

    result[result_len - 1] = '\0';

    return result;
}


char* atob(const char* s) {
    char *result = malloc(sizeof(char));

    int i = 0, mod, result_len = 1;
    size_t len = strlen(s);

    if(decode_table == NULL) {
        build_decode_table();
    }

    while (i < len) {

        if(s[i] == '=') {
            break;
        }
        mod = i % 4;
        switch (mod) {
            case 0:
                break;
            case 1:
                result_len++;
                result = realloc(result, result_len * sizeof(char));
                result[result_len-2] = decode_table[(int)s[i-1]] << 2 | decode_table[(int)s[i]] >> 4;
                break;
            case 2:
                result_len++;
                result = realloc(result, result_len * sizeof(char));
                result[result_len-2] = (decode_table[(int)s[i-1]] & 15) << 4 | decode_table[(int)s[i]] >> 2;
                break;
            case 3:
                result_len++;
                result = realloc(result, result_len * sizeof(char));
                result[result_len-2] = (decode_table[(int)s[i-1]] & 3) << 6 | decode_table[(int)s[i]];
                break;
        }
        i++;
    }

    result[result_len-1] = '\0';
    return result;
}
