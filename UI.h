#pragma once

#include "Service.h"
#include "macros.h"

typedef struct {
    Service* service;
} UI;

UI*  UI_create(Service* service);

void UI_destroy(UI* ui);

void UI_run(UI* ui);

void UI_printFile(File* file);

void UI_customGetLine(char* userInput);

void UI_addFile(UI* ui, char** inputTokens);

void UI_deleteFile(UI* ui, char** inputTokens);

void UI_updateFile(UI* ui, char** inputTokens);

void UI_listAllFiles(UI* ui);

void UI_listFilteredFiles(UI* ui, char** inputTokens);

void UI_listByYearOfCreation(UI* ui, char** inputTokens);

int  UI_checkIfStringIsNumber(char* string);

int  UI_checkIfCharacterIsDigit(char character);

void UI_undoLastOperation(UI* ui);

void UI_redoLastOperation(UI* ui);