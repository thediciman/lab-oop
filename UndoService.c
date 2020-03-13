#include "UndoService.h"

#include "Utils.h"

#include <stdlib.h>

UndoService* UndoService_create() {
    UndoService* undoService = (UndoService*) malloc(sizeof(UndoService));
    undoService->undoHistory = Container_create(Container_destroyWithElements);
    undoService->redoHistory = Container_create(Container_destroyWithElements);
    undoService->currentContainer = NULL;
    return undoService;
}

void UndoService_destroy(UndoService* undoService) {
    Container_destroyWithElements(undoService->undoHistory);
    Container_destroyWithElements(undoService->redoHistory);
    free(undoService);
}

void UndoService_addToHistory(UndoService* undoService, Container* previousContainer, Container* currentContainer) {
    Container_destroyWithElements(undoService->redoHistory);
    undoService->redoHistory = Container_create(Container_destroyWithElements);
    undoService->currentContainer = currentContainer;
    Container_pushElementToEnd(undoService->undoHistory, previousContainer);
}

Container* UndoService_undo(UndoService* undoService) {
    if (Container_size(undoService->undoHistory) == 0) {
        return NULL;
    }
    Container_pushElementToEnd(undoService->redoHistory, Utils_getDeepCopyOfFileContainer(undoService->currentContainer));
    Container* previousContainer = Container_popElementFromEnd(undoService->undoHistory);
    undoService->currentContainer = previousContainer;
    return previousContainer;
}

Container* UndoService_redo(UndoService* undoService) {
    if (Container_size(undoService->redoHistory) == 0) {
        return NULL;
    }
    Container_pushElementToEnd(undoService->undoHistory, Utils_getDeepCopyOfFileContainer(undoService->currentContainer));
    Container* previousContainer = Container_popElementFromEnd(undoService->redoHistory);
    undoService->currentContainer = previousContainer;
    return previousContainer;
}