#include <iostream>
#include <dlfcn.h>
#include <cstring>
#include "caesar.h"

int main() {

    void* handle = dlopen("./caesar.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    char* (*encrypt)(char*, int);
    encrypt = (char* (*)(char*, int)) dlsym(handle, "encrypt");
    if (!encrypt) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    char* (*decrypt)(char*, int);
    decrypt = (char* (*)(char*, int)) dlsym(handle, "decrypt");
    if (!decrypt) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    char text[] = "Roses are red, violets are blue";
    int key = 1;

    char* encryptedText = encrypt(text, key);
    std::cout << "Encrypted: " << encryptedText << std::endl;

    char* decryptedText = decrypt(encryptedText, key);
    std::cout << "Decrypted: " << decryptedText << std::endl;

    free(encryptedText);
    free(decryptedText);
    
    dlclose(handle);

    return 0;
}
