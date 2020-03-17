#include "UndoServiceTests.h"

#include "UndoService.h"
#include "Container.h"
#include "Domain.h"

#include "stdlib.h"
#include "assert.h"

void testUndoService() {
    UndoService_addToHistory__shouldUpdateTheHistories();
    UndoService_undo__shouldUpdateTheHistories();
    UndoService_redo__shouldUpdateTheHistories();
}

void UndoService_addToHistory__shouldUpdateTheHistories() {
    UndoService* undoService = UndoService_create();
    assert(undoService->currentContainer == NULL);
    assert(Container_size(undoService->undoHistory) == 0);
    assert(Container_size(undoService->redoHistory) == 0);
    Container* previousContainer = Container_create(File_destroy);
    Container* currentContainer = Container_create(File_destroy);
    UndoService_addToHistory(undoService, previousContainer, currentContainer);
    assert(undoService->currentContainer == currentContainer);
    assert(Container_size(undoService->undoHistory) == 1);
    assert(Container_size(undoService->redoHistory) == 0);
    Container_destroyWithElements(currentContainer);
    UndoService_destroy(undoService);
}

void UndoService_undo__shouldUpdateTheHistories() {
    UndoService* undoService = UndoService_create();
    assert(UndoService_undo(undoService) == NULL);
    Container* previousContainer = Container_create(File_destroy);
    Container* currentContainer = Container_create(File_destroy);
    UndoService_addToHistory(undoService, previousContainer, currentContainer);
    assert(UndoService_undo(undoService) != NULL);
    assert(Container_size(undoService->undoHistory) == 0);
    assert(Container_size(undoService->redoHistory) == 1);
    Container_destroyWithElements(currentContainer);
    Container_destroyWithElements(previousContainer);
    UndoService_destroy(undoService);
}

void UndoService_redo__shouldUpdateTheHistories() {
    UndoService* undoService = UndoService_create();
    assert(UndoService_redo(undoService) == NULL);
    Container* previousContainer = Container_create(File_destroy);
    Container* currentContainer = Container_create(File_destroy);
    UndoService_addToHistory(undoService, previousContainer, currentContainer);
    UndoService_undo(undoService);
    Container* redoneContainer = UndoService_redo(undoService);
    assert(redoneContainer != NULL);
    assert(Container_size(undoService->undoHistory) == 1);
    assert(Container_size(undoService->redoHistory) == 0);
    Container_destroyWithElements(redoneContainer);
    Container_destroyWithElements(previousContainer);
    Container_destroyWithElements(currentContainer);
    UndoService_destroy(undoService);
}