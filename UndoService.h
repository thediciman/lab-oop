#pragma once

#include "Container.h"

typedef struct {
    Container* undoHistory;
    Container* redoHistory;
    Container* currentContainer;
} UndoService;

/*
    Description:
        - Creates a new dynamically allocated UndoService and returns it.
    Inputs:
        - None.
    Outputs:
        - The newly allocated UndoService.
*/
UndoService* UndoService_create();

/*
    Description:
        - Destroys an UndoService.
    Inputs:
        - undoService: The UndoService to be destroyed.
    Outputs:
        - None.
*/
void UndoService_destroy(UndoService* undoService);

/*
    Description:
        - Adds a container to the undoHistory and sets the current container.
    Inputs:
        - undoService: The UndoService in which we add the container and set the current one.
        - previousContainer: The container to be added to the undoHistory.
        - currentContainer: The container to be set for the current one.
    Outputs:
        - None.
*/
void UndoService_addToHistory(UndoService* undoService, Container* previousContainer, Container* currentContainer);


/*
    Description:
        - Returns the corresponding container after an undo operation.
    Inputs:
        - undoService: The UndoService which manages the undo/redo operations.
    Outputs:
        - The container after the undo operation.
*/
Container* UndoService_undo(UndoService* undoService);

/*
    Description:
        - Returns the corresponding container after an redo operation.
    Inputs:
        - undoService: The UndoService which manages the undo/redo operations.
    Outputs:
        - The container after the redo operation.
*/
Container* UndoService_redo(UndoService* undoService);