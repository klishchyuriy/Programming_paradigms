#include "caesar_cipher.h"
#include <iostream>
#include <fstream>
#include <cstring>

extern "C" {
#include <dlfcn.h>
}

CaesarCipher::CaesarCipher(const char* libraryPath) {
    loadLibrary(libraryPath);
}

CaesarCipher::~CaesarCipher() {
    unloadLibrary();
}

void CaesarCipher::loadLibrary(const char* libraryPath) {
    libraryHandle = dlopen(libraryPath, RTLD_LAZY);
    if (!libraryHandle) {
        std::cerr << "Failed to load library: " << dlerror() << std::endl;
        throw std::runtime_error("Failed to load library");
    }
    encryptFunc = (EncryptDecryptFunc)dlsym(libraryHandle, "encrypt");
    decryptFunc = (EncryptDecryptFunc)dlsym(libraryHandle, "decrypt");
}

void CaesarCipher::unloadLibrary() {
    if (libraryHandle) {
        dlclose(libraryHandle);
    }
}

void CaesarCipher::encrypt(const char* input, char* output, int key) {
    encryptFunc(input, output, key);
}

void CaesarCipher::decrypt(const char* input, char* output, int key) {
    decryptFunc(input, output, key);
}
