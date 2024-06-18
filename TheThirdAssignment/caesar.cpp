#include "caesar.h"
#include <cstring>
#include <cctype>
#include <cstdlib>

char* encrypt(char* rawText, int key) {
    int len = strlen(rawText);
    char* encryptedText = (char*)malloc(len + 1);

    for (int i = 0; i < len; i++) {
        if (isalpha(rawText[i])) {
            char offset = islower(rawText[i]) ? 'a' : 'A';
            encryptedText[i] = ((rawText[i] - offset + key) % 26) + offset;
        } else {
            encryptedText[i] = rawText[i];
        }
    }
    encryptedText[len] = '\0';
    return encryptedText;
}
