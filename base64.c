#include "base64.h"
#include <string.h> // strlen()
#include <stdlib.h> // malloc() realloc()
#include <math.h> // ceil()

static const char *encode_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char decode_table[128];

static int decode_table_ready = 0;

void build_decode_table() {
    for (int i = 0; i < 64; i++) {
        decode_table[(unsigned char) encode_table[i]] = i;
    }
    decode_table_ready = 1;
}


char* btoa(const unsigned char* s) {
    size_t len = strlen((char*)s);
    char *result = malloc(sizeof(char) * (ceil(len * 8 / 6) + 1));
    int i = 0, mod, j = 1;


    while(i < len) {
        mod = i % 3;
        switch (mod) {
            case 0:
                j++;
                result[j-2] = encode_table[s[i] >> 2];
                break;
            case 1:
                j++;
                result[j-2] = encode_table[(s[i-1] & 3) << 4 | s[i] >> 4];
                break;
            case 2:
                j += 2;
                result[j-3] = encode_table[(s[i-1] & 15) << 2 | (s[i] >> 6)];
                result[j-2] = encode_table[s[i] & 63];
                break;
        }
        i++;
    }

    if (mod == 0) {
        j += 3;
        result[j - 4] = encode_table[(s[i-1] & 3) << 4];
        result[j - 3] = result[j - 2] = '=';
    } else if (mod == 1) {
        j += 2;
        result[j - 3] = encode_table[(s[i-1] & 15) << 2];
        result[j - 2] = '=';
    }

    result[j - 1] = '\0';

    return result;
}


char* atob(const char* s) {
    size_t len = strlen(s);
    size_t result_length = len / 4 * 3 + 1;
    if(s[len - 1] == '=') result_length--;
    if(s[len - 2] == '=') result_length--;

    char *result = malloc(sizeof(char) * result_length);

    int i = 0, mod, j = 1;


    if(!decode_table_ready) {
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
                j++;
                result[j-2] = decode_table[(int)s[i-1]] << 2 | decode_table[(int)s[i]] >> 4;
                break;
            case 2:
                j++;
                result[j-2] = (decode_table[(int)s[i-1]] & 15) << 4 | decode_table[(int)s[i]] >> 2;
                break;
            case 3:
                j++;
                result[j-2] = (decode_table[(int)s[i-1]] & 3) << 6 | decode_table[(int)s[i]];
                break;
        }
        i++;
    }

    result[j-1] = '\0';
    return result;
}
