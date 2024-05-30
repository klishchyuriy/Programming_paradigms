#include "text_editor.h"
#include <iostream>
#include <fstream>
#include <cstring>

Line::Line(const char *text) : next(nullptr), text(nullptr) {
    setText(text);
}

Line::~Line() {
    delete[] text;
}

const char* Line::getText() const {
    return text;
}

void Line::setText(const char *newText) {
    if (text) {
        delete[] text;
    }
    text = new char[strlen(newText) + 1];
    strcpy(text, newText);
}

void Line::appendText(const char *newText) {
    char *temp = new char[strlen(text) + strlen(newText) + 1];
    strcpy(temp, text);
    strcat(temp, newText);
    setText(temp);
    delete[] temp;
}

void Line::insertText(int charIndex, const char *newText) {
    if (charIndex < 0 || charIndex > static_cast<int>(strlen(text))) {
        std::cerr << "Invalid character index\n";
        return;
    }
    char *temp = new char[strlen(text) + strlen(newText) + 1];
    strncpy(temp, text, charIndex);
    temp[charIndex] = '\0';
    strcat(temp, newText);
    strcat(temp, text + charIndex);
    setText(temp);
    delete[] temp;
}

TextEditor::TextEditor() : head(nullptr) {}

TextEditor::~TextEditor() {
    clearText();
}

void TextEditor::appendText(const char *text) {
    if (!head) {
        startNewLine();
    }
    Line *current = head;
    while (current->next) {
        current = current->next;
    }
    current->appendText(text);
}

void TextEditor::startNewLine() {
    Line *newLine = new Line("");
    if (!head) {
        head = newLine;
    } else {
        Line *current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newLine;
    }
}

void TextEditor::saveToFile(const char *filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }
    Line *current = head;
    while (current) {
        file << current->getText() << "\n";
        current = current->next;
    }
    file.close();
}

void TextEditor::loadFromFile(const char *filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }
    clearText();
    char buffer[1024];
    while (file.getline(buffer, sizeof(buffer))) {
        startNewLine();
        appendText(buffer);
    }
    file.close();
}

void TextEditor::printCurrentText() const {
    Line *current = head;
    while (current) {
        std::cout << current->getText() << "\n";
        current = current->next;
    }
}

void TextEditor::insertText(int lineNumber, int charIndex, const char *text) {
    Line *current = head;
    for (int i = 0; i < lineNumber; ++i) {
        if (!current) {
            std::cerr << "Invalid line number\n";
            return;
        }
        current = current->next;
    }
    if (current) {
        current->insertText(charIndex, text);
    } else {
        std::cerr << "Invalid line number\n";
    }
}

void TextEditor::searchText(const char *query) const {
    Line *current = head;
    int lineNumber = 0;
    while (current) {
        const char *pos = strstr(current->getText(), query);
        while (pos) {
            std::cout << "Found at line " << lineNumber << ", character " << (pos - current->getText()) << "\n";
            pos = strstr(pos + 1, query);
        }
        current = current->next;
        lineNumber++;
    }
}

void TextEditor::clearText() {
    Line *current = head;
    while (current) {
        Line *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}
