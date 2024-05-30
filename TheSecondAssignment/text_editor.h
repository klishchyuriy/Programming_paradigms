#ifndef THESECONDASSIGNMENT_TEXT_EDITOR_H
#define THESECONDASSIGNMENT_TEXT_EDITOR_H

#include "string"
#include "vector"

class Line {
public:
    Line(const std::string &text = "");
    std::string getText() const;
    void appendText(const std::string &text);
    void insertText(int charIndex, const std::string &text);

private:
    std::string text;
};

class TextEditor {
public:
    TextEditor();
    void appendText(const std::string &text);
    void startNewLine();
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);
    void printCurrentText() const;
    void insertText(int lineNumber, int charIndex, const std::string &text);
    void searchText(const std::string &query) const;
    void clearText();

private:
    std::vector<Line> lines;
};

#endif
