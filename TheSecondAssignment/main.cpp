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
    std::cout << "8. Delete text by line, index, and number of symbols\n";
    std::cout << "9. Undo last command\n";
    std::cout << "10. Redo last command\n";
    std::cout << "11. Cut text\n";
    std::cout << "12. Paste text\n";
    std::cout << "13. Copy text\n";
    std::cout << "14. Insert text with replacement\n";
    std::cout << "15. Move cursor\n";
    std::cout << "16. Cut text at cursor\n";
    std::cout << "17. Copy text at cursor\n";
    std::cout << "18. Paste text at cursor\n";
    std::cout << "19. Delete text at cursor\n";
    std::cout << "20. Clear console\n";
    std::cout << "0. Exit\n";
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
                char text[1024];
                std::cout << "Enter text to append: ";
                std::cin.getline(text, 1024);
                editor.appendText(text);
            }
                break;
            case 2:
                editor.startNewLine();
                std::cout << "New line is started\n";
                break;
            case 3: {
                char filename[1024];
                std::cout << "Enter the file name for saving: ";
                std::cin.getline(filename, 1024);
                editor.saveToFile(filename);
            }
                break;
            case 4: {
                char filename[1024];
                std::cout << "Enter the file name for loading: ";
                std::cin.getline(filename, 1024);
                editor.loadFromFile(filename);
            }
                break;
            case 5:
                editor.printCurrentText();
                break;
            case 6: {
                int lineNumber, charIndex;
                char text[1024];
                std::cout << "Enter line number: ";
                std::cin >> lineNumber;
                std::cout << "Enter character index: ";
                std::cin >> charIndex;
                std::cin.ignore();
                std::cout << "Enter text to insert: ";
                std::cin.getline(text, 1024);
                editor.insertText(lineNumber, charIndex, text);
            }
                break;
            case 7: {
                char query[1024];
                std::cout << "Enter text to search: ";
                std::cin.getline(query, 1024);
                editor.searchText(query);
            }
                break;
            case 8: {
                int lineNumber, charIndex, numChars;
                std::cout << "Enter line number: ";
                std::cin >> lineNumber;
                std::cout << "Enter character index: ";
                std::cin >> charIndex;
                std::cout << "Enter number of characters to delete: ";
                std::cin >> numChars;
                std::cin.ignore();
                editor.deleteText(lineNumber, charIndex, numChars);
            }
                break;
            case 9:
                editor.undo();
                break;
            case 10:
                editor.redo();
                break;
            case 11: {
                int lineNumber, charIndex, numChars;
                std::cout << "Enter line number: ";
                std::cin >> lineNumber;
                std::cout << "Enter character index: ";
                std::cin >> charIndex;
                std::cout << "Enter number of characters to cut: ";
                std::cin >> numChars;
                std::cin.ignore();
                editor.cutText(lineNumber, charIndex, numChars);
            }
                break;
            case 12: {
                int lineNumber, charIndex;
                std::cout << "Enter line number: ";
                std::cin >> lineNumber;
                std::cout << "Enter character index: ";
                std::cin >> charIndex;
                std::cin.ignore();
                editor.pasteText(lineNumber, charIndex);
            }
                break;
            case 13: {
                int lineNumber, charIndex, numChars;
                std::cout << "Enter line number: ";
                std::cin >> lineNumber;
                std::cout << "Enter character index: ";
                std::cin >> charIndex;
                std::cout << "Enter number of characters to copy: ";
                std::cin >> numChars;
                std::cin.ignore();
                editor.copyText(lineNumber, charIndex, numChars);
            }
                break;
            case 14: {
                int lineNumber, charIndex;
                char text[1024];
                std::cout << "Enter line number: ";
                std::cin >> lineNumber;
                std::cout << "Enter character index: ";
                std::cin >> charIndex;
                std::cin.ignore();
                std::cout << "Enter text to replace: ";
                std::cin.getline(text, 1024);
                editor.insertTextWithReplacement(lineNumber, charIndex, text);
            }
                break;
            case 15: {
                int lineNumber, charIndex;
                std::cout << "Enter line number: ";
                std::cin >> lineNumber;
                std::cout << "Enter character index: ";
                std::cin >> charIndex;
                std::cin.ignore();
                editor.moveCursor(lineNumber, charIndex);
                std::cout << "Cursor moved to line " << lineNumber << ", index " << charIndex << "\n";
            }
                break;
            case 16: {
                int numChars;
                std::cout << "Enter number of characters to cut: ";
                std::cin >> numChars;
                std::cin.ignore();
                editor.cutTextAtCursor(numChars);
            }
                break;
            case 17: {
                int numChars;
                std::cout << "Enter number of characters to copy: ";
                std::cin >> numChars;
                std::cin.ignore();
                editor.copyTextAtCursor(numChars);
            }
                break;
            case 18:
                editor.pasteTextAtCursor();
                break;
            case 19: {
                int numChars;
                std::cout << "Enter number of characters to delete: ";
                std::cin >> numChars;
                std::cin.ignore();
                editor.deleteTextAtCursor(numChars);
            }
                break;
            case 20:
                editor.clearText();
                std::cout << "Console cleared\n";
                break;
            case 0:
                return 0;
            default:
                std::cerr << "Invalid command\n";
                break;
        }
    }
}
