#include "text_editor.h"
#include <iostream>
#include <fstream>

void readAndPrintFile(const char* filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string line;
        while (getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
}

int main() {
    const char* inputFile = "/Users/klishchyuriy/Desktop/Programming_paradigms/TheFourthAssignment/original.txt";
    const char* encryptedFile = "/Users/klishchyuriy/Desktop/Programming_paradigms/TheFourthAssignment/encrypted.txt";
    const char* decryptedFile = "/Users/klishchyuriy/Desktop/Programming_paradigms/TheFourthAssignment/decrypted.txt";

    int key;
    std::cout << "Enter the encryption/decryption key: ";
    std::cin >> key;

    TextEditor editor("/Users/klishchyuriy/Desktop/Programming_paradigms/TheFourthAssignment/cmake-build-debug/libcaesar.dylib");

    std::cout << "Encrypting the file..." << std::endl;
    editor.encryptFile(inputFile, encryptedFile, key);

    std::cout << "Encrypted content:" << std::endl;
    readAndPrintFile(encryptedFile);

    std::cout << "Decrypting the file..." << std::endl;
    editor.decryptFile(encryptedFile, decryptedFile, key);

    std::cout << "Decrypted content:" << std::endl;
    readAndPrintFile(decryptedFile);

    return 0;
}
