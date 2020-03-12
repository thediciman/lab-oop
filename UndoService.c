#include "UndoService.h"

#include <stdlib.h>

UndoService* UndoService_create() {
    UndoService* undoService = (UndoService*) malloc(sizeof(UndoService));
    undoService->history = Container_create(Container_destroy);
    return undoService;
}

void UndoService_destroy(UndoService* undoService) {
    free(undoService);
}

void UndoService_addToHistory(UndoService* undoService, Container* container) {
    Container_pushElementToEnd(undoService->history, container);
}
