#pragma once

#include "BonusUndoServiceUtils.h"

typedef struct {
    Container* history;
    int index;
    int duringOperation;
} BonusUndoService;

BonusUndoService* BonusUndoService_create();

void BonusUndoService_destroy(BonusUndoService* bonusUndoService);

void BonusUndoService_recordOperation(BonusUndoService* bonusUndoService, Operation* operation);

int BonusUndoService_undo(BonusUndoService* bonusUndoService);

int BonusUndoService_redo(BonusUndoService* bonusUndoService);