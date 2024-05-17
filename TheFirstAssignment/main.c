#include <stdio.h>
#include <string.h>
#include "text_editor.h"

void printMenu() {
    printf("Choose the command:\n");
    printf("1. Append text symbols to the end\n");
    printf("2. Start a new line\n");
    printf("3. Save to file\n");
    printf("4. Load from file\n");
    printf("5. Print current text\n");
    printf("6. Insert text by line and symbol index\n");
    printf("7. Search text\n");
    printf("8. Clear console\n");
    printf("0. Exit\n");
}

int main() {
    Line *head = NULL;
    int command;
    while (1) {
        printMenu();
        printf("> ");
        scanf("%d", &command);
        getchar();

        switch (command) {
            case 1: {
                char text[1024];
                printf("Enter text to append: ");
                fgets(text, sizeof(text), stdin);
                removeNewline(text);
                appendText(&head, text);
            }
                break;
        }
    }
}