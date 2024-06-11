#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <iostream>
#include <stack>

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
    void undo();
    void redo();

private:
    struct Line {
        char* text;
        Line* next;
    };
    Line* head;

    std::stack<Line*> undoStack;
    std::stack<Line*> redoStack;

    void removeNewline(char* str) const;
    void saveState(std::stack<Line*>& stack);
    void restoreState(std::stack<Line*>& stack);
};

#endif
