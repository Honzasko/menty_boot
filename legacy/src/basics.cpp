#include "../include/basics.hpp"

int basics::strlen(const char* text) {
    int len = 0;
    while (text[len] != 0)
        len++;
    return len;
}

int basics::strcmp(const char* a, const char* b, int len) {
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}