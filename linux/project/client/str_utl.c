#include "str_utl.h"

void splitString(const char *pstr, const char * delimiter, char *tokens[], int max_tokens, int * pcount) {
    int token_count = 0;
    char *token = strtok((char *)pstr, delimiter);
    while (token != NULL && token_count < max_tokens - 1) {
        char *pstr = (char *)calloc(1, strlen(token) + 1);
        strcpy(pstr, token);
        tokens[token_count++] = pstr;
        token = strtok(NULL, delimiter);
    }
    // 添加NULL终止符
    tokens[token_count] = NULL;
    *pcount = token_count;
}

void freeStrs(char *pstrs[], int count) {
    for (int i = 0; i < count; i++) {
        free(pstrs[i]);
    }
}
