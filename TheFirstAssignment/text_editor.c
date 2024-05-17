#include <stdlib.h>
#include <string.h>
#include "text_editor.h"


void removeNewline(char *str) {
    size_t length = strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}

void startNewLine(Line **head) {
    Line *newLine = malloc(sizeof(Line));
    newLine->text = malloc(1);
    newLine->text[0] = '\0';
    newLine->next = NULL;

    if (*head == NULL) {
        *head = newLine;
    } else {
        Line *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newLine;
    }
}

void appendText(Line **head, const char *text) {
    if (*head == NULL) {
        startNewLine(head);
    }
    Line *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    size_t newLength = strlen(current->text) + strlen(text) + 1;
    current->text = realloc(current->text, newLength);
    strcat(current->text, text);
}