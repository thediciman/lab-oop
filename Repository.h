#pragma once

#include "Container.h"

typedef struct {
    Container* container;
} Repository;

Repository* Repository_create();

void Repository_destroy(Repository* repository);

int Repository_indexOfElement(Repository* repository, TElem* element);

int Repository_addElement(Repository* repository, TElem* element);

int Repository_deleteElement(Repository* repository, TElem* element);

int Repository_deleteElementWithID(Repository* repository, int ID);

int Repository_updateElement(Repository* repository, TElem* element);

Container* Repository_getContainer(Repository* repository);