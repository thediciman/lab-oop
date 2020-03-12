#pragma once

#include "Container.h"

typedef struct {
    Container* history;
} UndoService;

UndoService* UndoService_create();

void UndoService_destroy(UndoService* undoService);

void UndoService_addToHistory(UndoService* undoService, Container* container);

Container* UndoService_popFromHistory(UndoService* undoService);