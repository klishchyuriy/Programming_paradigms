#ifndef CAESAR_H
#define CAESAR_H

extern "C" {
__attribute__((visibility("default"))) char* encrypt(char* rawText, int key);
__attribute__((visibility("default"))) char* decrypt(char* encryptedText, int key);
}

#endif
