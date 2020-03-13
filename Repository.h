#pragma once

#include "Container.h"

#include "Domain.h"

typedef struct {
    Container* container;
} Repository;

/*
    Description:
        - Creates a new dynamically allocated Repository and returns it.
    Inputs:
        - None.
    Outputs:
        - The newly allocated Repository.
*/
Repository* Repository_create();

/*
    Description:
        - Destroys a Repository, its container and the elements of the container.
    Inputs:
        - repository: pointer to the Repository that should be destroyed.
    Outputs:
        - None.
*/
void Repository_destroy(Repository* repository);

/*
    Description:
        - Returns the index of an element (by id) from the repository, if it exists.
    Inputs:
        - repository: The repository to search into.
        - element: The element to be searched for.
    Outputs:
        - The index of the element on success, -1 if the element was not found.
*/
int Repository_indexOfElement(Repository* repository, File* element);

/*
    Description:
        - Adds an element into a repository.
    Inputs:
        - repository: The repository to add the element into.
        - element: The element to be added.
    Outputs:
        - 0 on success, -4 if there already exists an element with that ID or whatever Container_expandIfCapacityReached returns otherwise.
*/
int Repository_addElement(Repository* repository, File* element);

/*
    Description:
        - Deletes and destroys an element from a repository.
    Inputs:
        - repository: The repository to delete the element from.
        - element: The element to be deleted from the repository.
    Outputs:
        - 0 on success, -5 if the element was not found.
*/
int Repository_deleteElement(Repository* repository, File* element);

/*
    Description:
        - Deletes and destroys the element with the given ID from a repository, if it exists.
    Inputs:
        - repository: The repository to delete the element from.
        - ID: the ID of the element to be deleted.
    Outputs:
        - 0 on success, -5 if the element was not found.
*/
int Repository_deleteElementWithID(Repository* repository, int ID);

/*
    Description:
        - Updates an element from a repository.
    Inputs:
        - repository: The repository on which we perform the update.
        - element: The element to be updated.
    Outputs:
        - 0 on success, -5 if the element was not found.
*/
int Repository_updateElement(Repository* repository, File* element);

/*
    Description:
        - Returns the Container of a Repository.
    Inputs:
        - repository: The repository whose container should be retrieved.
    Outputs:
        - The container of the repository.
*/
Container* Repository_getContainer(Repository* repository);

/*
    Description:
        - Replaces the container of a Repository with a new one.
    Inputs:
        - repository: The repository whose container will be replaced.
        - newContainer: The container that will replace the old container.
    Outputs:
        - None.
*/
void Repository_replaceContainer(Repository* repository, Container* newContainer);