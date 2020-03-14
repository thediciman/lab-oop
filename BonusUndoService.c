#include "BonusUndoService.h"
#include "Service.h"
#include <stdlib.h>
#include <stdio.h>

BonusUndoService* BonusUndoService_create() {
    BonusUndoService* bonusUndoService = (BonusUndoService*) malloc(sizeof(BonusUndoService));
    bonusUndoService->history = Container_create(Operation_destroy);
    bonusUndoService->index = 0;
    bonusUndoService->duringOperation = 0;
    return bonusUndoService;
}

void BonusUndoService_destroy(BonusUndoService* bonusUndoService) {
    Container_destroyWithElements(bonusUndoService->history);
    free(bonusUndoService);
}

void BonusUndoService_recordOperation(BonusUndoService* bonusUndoService, Operation* operation) {
    if (bonusUndoService->index != Container_size(bonusUndoService->history)) {
        while (Container_size(bonusUndoService->history) > bonusUndoService->index) {
            Operation_destroy(Container_popElementFromEnd(bonusUndoService->history));
        }
    }
    bonusUndoService->index += 1;
    Container_pushElementToEnd(bonusUndoService->history, operation);
}

int BonusUndoService_undo(BonusUndoService* bonusUndoService) {
    if (bonusUndoService->index == 0) {
        return -7;
    }
    bonusUndoService->index -= 1;
    bonusUndoService->duringOperation = 1;
    Operation_callUndo(Container_getElementAtIndex(bonusUndoService->history, bonusUndoService->index));
    bonusUndoService->duringOperation = 0;
    return 0;
}

int BonusUndoService_redo(BonusUndoService* bonusUndoService) {
    if (bonusUndoService->index == Container_size(bonusUndoService->history)) {
        return -7;
    }
    bonusUndoService->duringOperation = 1;
    Operation_callRedo(Container_getElementAtIndex(bonusUndoService->history, bonusUndoService->index));
    bonusUndoService->duringOperation = 0;
    bonusUndoService->index += 1;
    return 0;
}