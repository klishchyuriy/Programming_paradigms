#include <iostream>
#include "text_editor.h"

void printMenu() {
    std::cout << "Choose the command:\n";
    std::cout << "1. Append text symbols to the end\n";
    std::cout << "2. Start a new line\n";
    std::cout << "3. Save to file\n";
    std::cout << "4. Load from file\n";
    std::cout << "5. Print current text\n";
    std::cout << "6. Insert text by line and symbol index\n";
    std::cout << "7. Search text\n";
    std::cout << "8. Clear console\n";
    std::cout << "0. Exit\n";
}

void removeNewline(std::string &str) {
    if (!str.empty() && str.back() == '\n') {
        str.pop_back();
    }
}

int main() {
    TextEditor editor;
    int command;
    while (true) {
        printMenu();
        std::cout << "> ";
        std::cin >> command;
        std::cin.ignore();

        switch (command) {
            case 1: {
                std::string text;
                std::cout << "Enter text to append: ";
                std::getline(std::cin, text);
                removeNewline(text);
                editor.appendText(text);
                break;
            }
            case 2:
                editor.startNewLine();
                std::cout << "New line is started\n";
                break;
            case 3: {
                std::string filename;
                std::cout << "Enter the file name for saving: ";
                std::getline(std::cin, filename);
                removeNewline(filename);
                editor.saveToFile(filename);
                std::cout << "Text has been saved successfully\n";
                break;
            }
            case 4: {
                std::string filename;
                std::cout << "Enter the file name for loading: ";
                std::getline(std::cin, filename);
                removeNewline(filename);
                editor.loadFromFile(filename);
                std::cout << "Text has been loaded successfully\n";
                break;
            }
            case 5:
                editor.printCurrentText();
                break;
            case 6: {
                int lineNumber, charIndex;
                std::string text;
                std::cout << "Enter line number and character index: ";
                std::cin >> lineNumber >> charIndex;
                std::cin.ignore();
                std::cout << "Enter text to insert: ";
                std::getline(std::cin, text);
                removeNewline(text);
                editor.insertText(lineNumber, charIndex, text);
                break;
            }
            case 7: {
                std::string query;
                std::cout << "Enter text to search: ";
                std::getline(std::cin, query);
                removeNewline(query);
                editor.searchText(query);
                break;
            }
            case 8:
                std::cout << "\033[2J\033[1;1H";
                break;
            case 0:
                editor.clearText();
                std::cout << "Exiting the editor...\n";
                return 0;
            default:
                std::cout << "Invalid command, please try again.\n";
                break;
        }
    }
}

