#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H

class CaesarCipher {
public:
    CaesarCipher(const char* libraryPath);
    ~CaesarCipher();

    void encrypt(const char* input, char* output, int key);
    void decrypt(const char* input, char* output, int key);

private:
    typedef void (*EncryptDecryptFunc)(const char*, char*, int);
    EncryptDecryptFunc encryptFunc;
    EncryptDecryptFunc decryptFunc;
    void* libraryHandle;

    void loadLibrary(const char* libraryPath);
    void unloadLibrary();
};

#endif // CAESAR_CIPHER_H
