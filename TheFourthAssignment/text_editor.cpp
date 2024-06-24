#include "text_editor.h"
#include <iostream>
#include <fstream>
#include <cstring>

TextEditor::TextEditor(const char* libraryPath) : caesarCipher(libraryPath) {}

void TextEditor::run() {
}

void TextEditor::encryptFile(const char* inputFile, const char* outputFile, int key) {
    const size_t CHUNK_SIZE = 1024;
    char inputChunk[CHUNK_SIZE];
    char outputChunk[CHUNK_SIZE];

    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Failed to open file for encryption." << std::endl;
        return;
    }

    while (inFile.read(inputChunk, CHUNK_SIZE) || inFile.gcount() > 0) {
        size_t bytesRead = inFile.gcount();
        caesarCipher.encrypt(inputChunk, outputChunk, key);
        outFile.write(outputChunk, bytesRead);
    }

    inFile.close();
    outFile.close();
}

void TextEditor::decryptFile(const char* inputFile, const char* outputFile, int key) {
    const size_t CHUNK_SIZE = 1024;
    char inputChunk[CHUNK_SIZE];
    char outputChunk[CHUNK_SIZE];

    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Failed to open file for decryption." << std::endl;
        return;
    }

    while (inFile.read(inputChunk, CHUNK_SIZE) || inFile.gcount() > 0) {
        size_t bytesRead = inFile.gcount();
        caesarCipher.decrypt(inputChunk, outputChunk, key);
        outFile.write(outputChunk, bytesRead);
    }

    inFile.close();
    outFile.close();
}
