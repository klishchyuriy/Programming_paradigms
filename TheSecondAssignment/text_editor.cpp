#include "text_editor.h"
#include <iostream>
#include <fstream>

Line::Line(const std::string &text) : text(text) {}

std::string Line::getText() const {
    return text;
}

void Line::appendText(const std::string &text) {
    this->text += text;
}

void Line::insertText(int charIndex, const std::string &text) {
    if (charIndex < 0 || charIndex > static_cast<int>(this->text.length())) {
        std::cerr << "Invalid character index\n";
        return;
    }
    this->text.insert(charIndex, text);
}

TextEditor::TextEditor() {}

void TextEditor::appendText(const std::string &text) {
    if (lines.empty()) {
        startNewLine();
    }
    lines.back().appendText(text);
}

void TextEditor::startNewLine() {
    lines.emplace_back("");
}

void TextEditor::saveToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }
    for (const auto &line : lines) {
        file << line.getText() << "\n";
    }
}

void TextEditor::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }
    clearText();
    std::string buffer;
    while (std::getline(file, buffer)) {
        startNewLine();
        appendText(buffer);
    }
}

void TextEditor::printCurrentText() const {
    for (const auto &line : lines) {
        std::cout << line.getText() << "\n";
    }
}

void TextEditor::insertText(int lineNumber, int charIndex, const std::string &text) {
    if (lineNumber < 0 || lineNumber >= static_cast<int>(lines.size())) {
        std::cerr << "Invalid line number\n";
        return;
    }
    lines[lineNumber].insertText(charIndex, text);
}

void TextEditor::searchText(const std::string &query) const {
    for (size_t i = 0; i < lines.size(); ++i) {
        const auto &line = lines[i];
        size_t pos = line.getText().find(query);
        while (pos != std::string::npos) {
            std::cout << "Found at line " << i << ", character " << pos << "\n";
            pos = line.getText().find(query, pos + 1);
        }
    }
}

void TextEditor::clearText() {
    lines.clear();
}