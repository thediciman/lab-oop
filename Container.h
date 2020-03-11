#pragma once

#include "Domain.h"

typedef File TElem;

typedef struct {
    TElem** data;
    int size;
    int capacity;
} Container;

Container* Container_create();

void Container_destroy(Container* container);

int Container_expandIfCapacityReached(Container* container);

int Container_pushElementToEnd(Container* container, TElem* element);

TElem* Container_getElementAtIndex(Container* container, int index);

int Container_deleteElementAtIndex(Container* container, int index);

int Container_updateElementAtIndex(Container* container, TElem* element, int index);

int Container_size(Container* container);

int Container_swapElementsAtIndices(Container* container, int firstIndex, int secondIndex);