#include "UI.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UI_MAX_TOKENS_ARRAY_LENGTH 8
#define UI_MAX_USER_INPUT_LENGTH 2048

int UI_checkIfCharacterIsDigit(char character) {
    return character >= '0' && character <= '9';
}

int UI_checkIfStringIsNumber(char* string) {
    for (int i = 0; i < strlen(string); ++i) {
        if (!UI_checkIfCharacterIsDigit(string[i])) {
            return 0;
        }
    }
    return 1;
}

UI* UI_create(Service* service) {
    UI* ui = (UI*) malloc(sizeof(UI));
    ui->service = service;
    return ui;
}

void UI_addFile(UI* ui, char** inputTokens) {
    int resultCode = Service_addFile(ui->service, atoi(inputTokens[1]), inputTokens[2], inputTokens[3], atoi(inputTokens[4]));
    if (resultCode != 0) {
        printf("No!\n");
    }
}

void UI_updateFile(UI* ui, char** inputTokens) {
    Service_updateFile(ui->service, atoi(inputTokens[1]), inputTokens[2], inputTokens[3], atoi(inputTokens[4]));
}

void UI_deleteFile(UI* ui, char** inputTokens) {
    int resultCode = Service_deleteFile(ui->service, atoi(inputTokens[1]));
    if (resultCode != 0) {
        printf("No!\n");
    }
}

void UI_listAllFiles(UI* ui) {
    Container* allFiles = Service_getAllFiles(ui->service);
    for (int i = 0; i < Container_size(allFiles); ++i) {
        UI_printFile(Container_getElementAtIndex(allFiles, i));
    }
}

void UI_listFilteredFiles(UI* ui, char** inputTokens) {
    Container* filteredFiles = Service_getFilesByFileType(ui->service, inputTokens[1]);
    for (int i = 0; i < Container_size(filteredFiles); ++i) {
        UI_printFile(Container_getElementAtIndex(filteredFiles, i));
    }
    Container_destroyWithoutElements(filteredFiles);
}

void UI_listByYearOfCreation(UI* ui, char** inputTokens) {
    Container* filteredFiles = Service_getFilesByYearOfCreation(ui->service, atoi(inputTokens[1]));
    for (int i = 0; i < Container_size(filteredFiles); ++i) {
        UI_printFile(Container_getElementAtIndex(filteredFiles, i));
    }
    Container_destroyWithoutElements(filteredFiles);
}

void UI_customGetLine(char* userInput) {
    char currentCharacter;
    int currentIndex = 0;
    while (1) {
        scanf("%c", &currentCharacter);
        if (currentCharacter == '\n') {
            break;
        }
        userInput[currentIndex++] = currentCharacter;
    }
    userInput[currentIndex] = 0;
}

void UI_run(UI* ui) {
    char userInput[UI_MAX_USER_INPUT_LENGTH];
    char* userInputTokens[UI_MAX_TOKENS_ARRAY_LENGTH];

    while (1) {
        UI_customGetLine(userInput);

        if (strcmp(userInput, "exit") == 0) {
            break;
        }

        int currentTokenIndex = 0;
        char* currentToken = strtok(userInput, " ,");
        while (currentToken != NULL) {
            userInputTokens[currentTokenIndex++] = currentToken;
            currentToken = strtok(NULL, " ,");
        }

        if (strcmp(userInputTokens[0], "add") == 0) {
            UI_addFile(ui, userInputTokens);
        } else if (strcmp(userInputTokens[0], "update") == 0) {
            UI_updateFile(ui, userInputTokens);            
        } else if (strcmp(userInputTokens[0], "delete") == 0) {
            UI_deleteFile(ui, userInputTokens);
        } else if (strcmp(userInputTokens[0], "list") == 0) {
            if (currentTokenIndex == 1) {
                UI_listAllFiles(ui);
            } else {
                if (UI_checkIfStringIsNumber(userInputTokens[1])) {
                    UI_listByYearOfCreation(ui, userInputTokens);
                } else {
                    UI_listFilteredFiles(ui, userInputTokens);
                }
            }
        } else if (strcmp(userInputTokens[0], "undo") == 0) {
            UI_undoLastOperation(ui);
        } else if (strcmp(userInputTokens[0], "redo") == 0) {
            UI_redoLastOperation(ui);
        }
    }
}

void UI_undoLastOperation(UI* ui) {
    Service_undoLastOperation(ui->service);
}

void UI_redoLastOperation(UI* ui) {
    Service_redoLastOperation(ui->service);
}

void UI_printFile(File* file) {
    printf("%d %s %s %d\n", File_getArchiveCatalogueNumber(file), File_getStateOfDeterioration(file), File_getFileType(file), File_getYearOfCreation(file));
}

void UI_destroy(UI* ui) {
    free(ui);
}