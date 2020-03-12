#include "UndoService.h"

#include <stdio.h>
#include <stdlib.h>

UndoService* UndoService_create() {
    UndoService* undoService = (UndoService*) malloc(sizeof(UndoService));
    undoService->history = Container_create(Container_destroyWithElements);
    return undoService;
}

void UndoService_destroy(UndoService* undoService) {
    Container_destroyWithElements(undoService->history);
    free(undoService);
}

void UndoService_addToHistory(UndoService* undoService, Container* container) {
    Container_pushElementToEnd(undoService->history, container);
}

Container* UndoService_popFromHistory(UndoService* undoService) {
    if (Container_size(undoService->history) == 0) {
        return NULL;
    }
    Container* previousState = Container_popElementFromEnd(undoService->history);
    return previousState;
}