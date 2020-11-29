//
// Created by sakost on 27.11.2020.
//

#include "realization.h"

#include <stdlib.h>
#include <string.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointers"
char* translation(long x){
    char *res = calloc(1, sizeof(char));
    res[0] = '\0';
    if(x == 0){
        char *tmp = calloc(strlen(res) + 2, sizeof(char));
        strcpy(tmp+1, res);
        free(res);
        res = tmp;
        res[0] = '0';
    }
    while(x > 0){
        char ch = (x & 1u) + '0';
        x >>= 1u;
        char *tmp = calloc(strlen(res) + 2, sizeof(char));
        strcpy(tmp+1, res);
        free(res);
        res = tmp;
        res[0] = ch;
    }
    return res;
}
#pragma clang diagnostic pop
