#include "text_editor.h"
#include <iostream>

TextEditor::TextEditor(const char* libraryPath) : caesarCipher(libraryPath) {}

void TextEditor::run() {
    int choice;
    std::cout << "Choose operation:\n1. Encrypt\n2. Decrypt\n";
    std::cin >> choice;

    if (choice == 1) {
        char input[256], output[256];
        int key;
        std::cout << "Enter text to encrypt: ";
        std::cin.ignore();
        std::cin.getline(input, 256);
        std::cout << "Enter key: ";
        std::cin >> key;
        encrypt(input, output, key);
        std::cout << "Encrypted text: " << output << std::endl;
    } else if (choice == 2) {
        char input[256], output[256];
        int key;
        std::cout << "Enter text to decrypt: ";
        std::cin.ignore();
        std::cin.getline(input, 256);
        std::cout << "Enter key: ";
        std::cin >> key;
        decrypt(input, output, key);
        std::cout << "Decrypted text: " << output << std::endl;
    } else {
        std::cerr << "Invalid choice\n";
    }
}

void TextEditor::encrypt(const char* input, char* output, int key) {
    caesarCipher.encrypt(input, output, key);
}

void TextEditor::decrypt(const char* input, char* output, int key) {
    caesarCipher.decrypt(input, output, key);
}
