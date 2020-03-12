#include "Container.h"

#include <stdlib.h>

Container* Container_create(DestroyElementFunction destroyFunction) {
    Container* container = (Container*) malloc(sizeof(Container));
    container->size = 0;
    container->capacity = 0;
    container->data = NULL;
    container->destroyFunction = destroyFunction;
    return container;
}

void Container_destroy(void* container) {
    free(((Container*) container)->data);
    free(container);
}

int Container_expandIfCapacityReached(Container* container) {
    if (container->size == container->capacity) {
        if (container->capacity == 0) {
            container->capacity = 1;
        } else {
            container->capacity *= 2;
        }
        TElem* dataCopy = container->data;
        container->data = (TElem*) malloc(container->capacity * sizeof(TElem));
        if (container->data == NULL) {
            free(dataCopy);
            return -1;
        }
        for (int i = 0; i < container->size; ++i) {
            container->data[i] = dataCopy[i];
        }
        free(dataCopy);
    }
    return 0;
}

int Container_pushElementToEnd(Container* container, TElem element) {
    int expansionResult = Container_expandIfCapacityReached(container);
    if (expansionResult != 0) {
        return expansionResult;
    }
    container->data[container->size] = element;
    ++container->size;
    return 0;
}

TElem Container_getElementAtIndex(Container* container, int index) {
    if (index < 0 || index >= container->size) {
        return NULL;
    }
    return container->data[index];
}

int Container_deleteElementAtIndex(Container* container, int index) {
    if (index < 0 || index >= container->size) {
        return -2;
    }
    container->destroyFunction(container->data[index]);
    for (int i = index; i < container->size - 1; ++i) {
        container->data[i] = container->data[i + 1];
    }
    --container->size;
    return 0;
}

int Container_updateElementAtIndex(Container* container, TElem element, int index) {
    if (index < 0 || index >= container->size) {
        return -2;
    }
    container->destroyFunction(container->data[index]);
    container->data[index] = element;
    return 0;
}

int Container_size(Container* container) {
    return container->size;
}

int Container_swapElementsAtIndices(Container* container, int firstIndex, int secondIndex) {
    if (
        (firstIndex < 0 || firstIndex >= container->size) ||
        (secondIndex < 0 || secondIndex >= container->size)
    ) {
        return -2;
    }
    TElem firstElementPointerCopy = container->data[firstIndex];
    container->data[firstIndex] = container->data[secondIndex];
    container->data[secondIndex] = firstElementPointerCopy;
    return 0;
}