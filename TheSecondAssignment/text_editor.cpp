#include "text_editor.h"
#include <cstring>
#include <fstream>

TextEditor::TextEditor() : head(nullptr), cursorLine(0), cursorIndex(0) {
    clipboard[0] = '\0';
}

TextEditor::~TextEditor() {
    clearText();
}

void TextEditor::saveState(std::stack<Line*>& stack) {
    Line* newState = nullptr;
    Line* current = head;
    Line** newCurrent = &newState;
    while (current) {
        *newCurrent = new Line{strdup(current->text), nullptr};
        current = current->next;
        newCurrent = &((*newCurrent)->next);
    }
    stack.push(newState);
}

void TextEditor::restoreState(std::stack<Line*>& stack) {
    if (stack.empty()) {
        std::cerr << "No more states to restore\n";
        return;
    }
    deleteLines(head);
    head = stack.top();
    stack.pop();
    cursorLine = 0;
    cursorIndex = 0;
}

void TextEditor::deleteLines(Line* lines) {
    while (lines) {
        Line* next = lines->next;
        delete[] lines->text;
        delete lines;
        lines = next;
    }
}

void TextEditor::appendText(const char* text) {
    saveState(undoStack);
    while (!redoStack.empty()) redoStack.pop();
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
    adjustCursorForLineLength();
}

void TextEditor::startNewLine() {
    saveState(undoStack);
    while (!redoStack.empty()) redoStack.pop();
    if (!head) {
        head = new Line{strdup(""), nullptr};
    } else {
        Line* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new Line{strdup(""), nullptr};
    }
    cursorLine++;
    cursorIndex = 0;
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
    saveState(undoStack);
    while (!redoStack.empty()) redoStack.pop();
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        deleteLines(head);
        head = nullptr;
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
    cursorLine = 0;
    cursorIndex = 0;
}

void TextEditor::printCurrentText() const {
    Line* current = head;
    while (current) {
        std::cout << current->text << "\n";
        current = current->next;
    }
}

void TextEditor::insertText(int lineNumber, int charIndex, const char* text) {
    saveState(undoStack);
    while (!redoStack.empty()) redoStack.pop();
    Line* current = getLine(lineNumber);
    if (!current || charIndex < 0 || charIndex > (int) strlen(current->text)) {
        std::cerr << "Invalid line number or character index\n";
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
    adjustCursorForLineLength();
}

void TextEditor::insertTextWithReplacement(int lineNumber, int charIndex, const char* text) {
    saveState(undoStack);
    while (!redoStack.empty()) redoStack.pop();
    Line* current = getLine(lineNumber);
    if (!current || charIndex < 0 || charIndex > (int) strlen(current->text)) {
        std::cerr << "Invalid line number or character index\n";
        return;
    }
    size_t textLen = strlen(text);
    size_t currentTextLen = strlen(current->text);
    size_t remainingTextLen = currentTextLen - charIndex;
    size_t newLength = charIndex + textLen + remainingTextLen + 1;
    char* newText = new char[newLength];
    strncpy(newText, current->text, charIndex);
    newText[charIndex] = '\0';
    strcat(newText, text);
    strcat(newText, current->text + charIndex);
    delete[] current->text;
    current->text = newText;
    adjustCursorForLineLength();
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
    saveState(undoStack);
    while (!redoStack.empty()) redoStack.pop(); // Clear redo stack
    deleteLines(head);
    head = nullptr;
    cursorLine = 0;
    cursorIndex = 0;
}

void TextEditor::deleteText(int lineNumber, int charIndex, int numChars) {
    saveState(undoStack);
    while (!redoStack.empty()) redoStack.pop(); // Clear redo stack
    Line* current = getLine(lineNumber);
    if (!current || charIndex < 0 || charIndex >= (int) strlen(current->text)) {
        std::cerr << "Invalid line number or character index\n";
        return;
    }
    if (charIndex + numChars > (int) strlen(current->text)) {
        numChars = strlen(current->text) - charIndex;
    }
    strncpy(clipboard, current->text + charIndex, numChars);
    clipboard[numChars] = '\0';
    size_t newLength = strlen(current->text) - numChars + 1;
    char* newText = new char[newLength];
    strncpy(newText, current->text, charIndex);
    newText[charIndex] = '\0';
    strcat(newText, current->text + charIndex + numChars);
    delete[] current->text;
    current->text = newText;
    adjustCursorForLineLength();
}

void TextEditor::deleteTextAtCursor(int numChars) {
    deleteText(cursorLine, cursorIndex, numChars);
}

void TextEditor::cutText(int lineNumber, int charIndex, int numChars) {
    saveState(undoStack);
    while (!redoStack.empty()) redoStack.pop();
    deleteText(lineNumber, charIndex, numChars);
}

void TextEditor::cutTextAtCursor(int numChars) {
    cutText(cursorLine, cursorIndex, numChars);
}

void TextEditor::copyText(int lineNumber, int charIndex, int numChars) {
    Line* current = getLine(lineNumber);
    if (!current || charIndex < 0 || charIndex >= (int) strlen(current->text)) {
        std::cerr << "Invalid line number or character index\n";
        return;
    }
    if (charIndex + numChars > (int) strlen(current->text)) {
        numChars = strlen(current->text) - charIndex;
    }
    strncpy(clipboard, current->text + charIndex, numChars);
    clipboard[numChars] = '\0';
}

void TextEditor::copyTextAtCursor(int numChars) {
    copyText(cursorLine, cursorIndex, numChars);
}

void TextEditor::pasteText(int lineNumber, int charIndex) {
    saveState(undoStack);
    while (!redoStack.empty()) redoStack.pop();
    insertText(lineNumber, charIndex, clipboard);
}

void TextEditor::pasteTextAtCursor() {
    pasteText(cursorLine, cursorIndex);
}

void TextEditor::moveCursor(int lineNumber, int charIndex) {
    cursorLine = lineNumber;
    cursorIndex = charIndex;
    adjustCursorForLineLength();
}

void TextEditor::moveCursorBy(int lineOffset, int charOffset) {
    cursorLine += lineOffset;
    cursorIndex += charOffset;
    adjustCursorForLineLength();
}

void TextEditor::adjustCursorForLineLength() {
    Line* current = getLine(cursorLine);
    if (current) {
        int lineLength = strlen(current->text);
        if (cursorIndex > lineLength) {
            cursorIndex = lineLength;
        }
    } else {
        cursorLine = 0;
        cursorIndex = 0;
    }
}

void TextEditor::undo() {
    if (!undoStack.empty()) {
        saveState(redoStack);
        restoreState(undoStack);
    } else {
        std::cerr << "No more states to undo\n";
    }
}

void TextEditor::redo() {
    if (!redoStack.empty()) {
        saveState(undoStack);
        restoreState(redoStack);
    } else {
        std::cerr << "No more states to redo\n";
    }
}

TextEditor::Line* TextEditor::getLine(int lineNumber) {
    Line* current = head;
    for (int i = 0; i < lineNumber; ++i) {
        if (!current) {
            return nullptr;
        }
        current = current->next;
    }
    return current;
}

void TextEditor::removeNewline(char* str) const {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
