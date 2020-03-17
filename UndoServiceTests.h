#pragma once

void testUndoService();

void UndoService_addToHistory__shouldUpdateTheHistories();

void UndoService_undo__shouldUpdateTheHistories();

void UndoService_redo__shouldUpdateTheHistories();