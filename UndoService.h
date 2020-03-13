#pragma once

#include "Container.h"

typedef struct {
    Container* undoHistory;
    Container* redoHistory;
    Container* currentContainer;
} UndoService;

UndoService* UndoService_create();

void UndoService_destroy(UndoService* undoService);

void UndoService_addToHistory(UndoService* undoService, Container* previousContainer, Container* currentContainer);

Container* UndoService_undo(UndoService* undoService);

Container* UndoService_redo(UndoService* undoService);