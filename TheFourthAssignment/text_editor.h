#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include "caesar_cipher.h"

class TextEditor {
public:
    TextEditor(const char* libraryPath);

    void run();
    void encryptFile(const char* inputFile, const char* outputFile, int key);
    void decryptFile(const char* inputFile, const char* outputFile, int key);

private:
    CaesarCipher caesarCipher;
};

#endif
