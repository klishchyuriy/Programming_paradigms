#include "text_editor.h"
#include <iostream>
#include <fstream>
#include <cstring>

void readFileContent(const char* filename, char* content, size_t maxLength) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
        return;
    }
    inFile.read(content, maxLength);
    content[inFile.gcount()] = '\0';
    inFile.close();
}

void writeFileContent(const char* filename, const char* content) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
        return;
    }
    outFile.write(content, std::strlen(content));
    outFile.close();
}

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

    char originalContent[1024];
    std::cout << "Original content:" << std::endl;
    readFileContent(inputFile, originalContent, sizeof(originalContent));
    std::cout << originalContent << std::endl;

    TextEditor editor("/Users/klishchyuriy/Desktop/Programming_paradigms/TheFourthAssignment/cmake-build-debug/libcaesar.dylib");

    char encryptedContent[1024];
    std::cout << "Encrypting the file..." << std::endl;
    editor.encrypt(originalContent, encryptedContent, key);
    writeFileContent(encryptedFile, encryptedContent);

    std::cout << "Encrypted content:" << std::endl;
    readAndPrintFile(encryptedFile);

    char decryptedContent[1024];
    std::cout << "Decrypting the file..." << std::endl;
    editor.decrypt(encryptedContent, decryptedContent, key);
    writeFileContent(decryptedFile, decryptedContent);

    std::cout << "Decrypted content:" << std::endl;
    readAndPrintFile(decryptedFile);

    return 0;
}
