#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include "caesar_cipher.h"

class TextEditor {
public:
    TextEditor(const char* libraryPath);

    void run();
    void encrypt(const char* input, char* output, int key);
    void decrypt(const char* input, char* output, int key);

private:
    CaesarCipher caesarCipher;
};

#endif
