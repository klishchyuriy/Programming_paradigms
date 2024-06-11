#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <iostream>

class TextEditor {
public:
    TextEditor();
    ~TextEditor();

    void appendText(const char* text);
    void startNewLine();
    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);
    void printCurrentText() const;
    void insertText(int lineNumber, int charIndex, const char* text);
    void searchText(const char* query) const;
    void clearText();
    void deleteText(int lineNumber, int charIndex, int numChars);

private:
    struct Line {
        char* text;
        Line* next;
    };
    Line* head;

    void removeNewline(char* str) const;
};

#endif
