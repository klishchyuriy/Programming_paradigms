#include "text_editor.h"
#include <cstring>
#include <fstream>

TextEditor::TextEditor() : head(nullptr) {
}

TextEditor::~TextEditor() {
    clearText();
}

void TextEditor::appendText(const char* text) {
    if (!head) {
        head = new Line{strdup(text), nullptr};
    } else {
        Line* current = head;
        while (current->next) {
            current = current->next;
        }
        size_t newLength = strlen(current->text) + strlen(text) + 1;
        char* newText = new char[newLength];
        strcpy(newText, current->text);
        strcat(newText, text);
        delete[] current->text;
        current->text = newText;
    }
}

void TextEditor::startNewLine() {
    if (!head) {
        head = new Line{strdup(""), nullptr};
    } else {
        Line* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new Line{strdup(""), nullptr};
    }
}

void TextEditor::saveToFile(const char* filename) const {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        Line* current = head;
        while (current) {
            outFile << current->text << "\n";
            current = current->next;
        }
        outFile.close();
        std::cout << "Text has been saved successfully\n";
    } else {
        std::cerr << "Unable to open file for saving\n";
    }
}

void TextEditor::loadFromFile(const char* filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        clearText();
        std::string line;
        while (getline(inFile, line)) {
            removeNewline(&line[0]);
            appendText(line.c_str());
            startNewLine();
        }
        inFile.close();
        std::cout << "Text has been loaded successfully\n";
    } else {
        std::cerr << "Unable to open file for loading\n";
    }
}

void TextEditor::printCurrentText() const {
    Line* current = head;
    while (current) {
        std::cout << current->text << "\n";
        current = current->next;
    }
}

void TextEditor::insertText(int lineNumber, int charIndex, const char* text) {
    Line* current = head;
    for (int i = 0; i < lineNumber; ++i) {
        if (!current) {
            std::cerr << "Invalid line number\n";
            return;
        }
        current = current->next;
    }
    if (charIndex < 0 || charIndex > (int) strlen(current->text)) {
        std::cerr << "Invalid character index\n";
        return;
    }
    size_t newLength = strlen(current->text) + strlen(text) + 1;
    char* newText = new char[newLength];
    strncpy(newText, current->text, charIndex);
    newText[charIndex] = '\0';
    strcat(newText, text);
    strcat(newText, current->text + charIndex);
    delete[] current->text;
    current->text = newText;
}

void TextEditor::searchText(const char* query) const {
    Line* current = head;
    int lineNumber = 0;
    while (current) {
        const char* pos = strstr(current->text, query);
        while (pos) {
            std::cout << "Found at line " << lineNumber << ", character " << pos - current->text << "\n";
            pos = strstr(pos + 1, query);
        }
        current = current->next;
        lineNumber++;
    }
}

void TextEditor::clearText() {
    Line* current = head;
    while (current) {
        Line* next = current->next;
        delete[] current->text;
        delete current;
        current = next;
    }
    head = nullptr;
}

void TextEditor::removeNewline(char* str) const {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}