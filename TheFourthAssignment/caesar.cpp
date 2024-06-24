#include <cctype>

extern "C" {
void encrypt(const char* input, char* output, int key) {
    key = key % 26;
    int i = 0;
    while (input[i] != '\0') {
        char ch = input[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            output[i] = (ch - base + key) % 26 + base;
        } else {
            output[i] = ch;
        }
        i++;
    }
    output[i] = '\0';
}

void decrypt(const char* input, char* output, int key) {
    key = key % 26;
    int i = 0;
    while (input[i] != '\0') {
        char ch = input[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            output[i] = (ch - base - key + 26) % 26 + base;
        } else {
            output[i] = ch;
        }
        i++;
    }
    output[i] = '\0';
}
}
