#include <iostream>
#include "caesar.h"

int main() {
    char text[] = "Roses are red, violets are blue";
    int key = 1;

    char* encryptedText = encrypt(text, key);
    std::cout << "Encrypted: " << encryptedText << std::endl;

    char* decryptedText = decrypt(encryptedText, key);
    std::cout << "Decrypted: " << decryptedText << std::endl;

    free(encryptedText);
    free(decryptedText);

    return 0;
}
