#include "ContainerTests.h"

#include "Container.h"
#include "Domain.h"

#include <stdlib.h>
#include <assert.h>

#define INSTANCE_OF_GENERIC_FILE File_create(0, "", "", 0)

void testContainer() {
    Container_expandIfCapacityReached__whenCapacityIsZero__expandsCapacityToOne();
    Container_expandIfCapacityReached__whenCapacityNotZero__doublesCapacity();
    Container_pushElementToEnd__validInput__appendsElement();
    Container_getElementAtIndex__validIndex__returnsElement();
    Container_getElementAtIndex__invalidIndex__returnsNULL();
    Container_deleteElementAtIndex__validIndex__returnsSuccess();
    Container_deleteElementAtIndex__invalidIndex__returnsErrorCode();
    Container_updateElementAtIndex__validIndex__returnsSuccess();
    Container_updateElementAtIndex__invalidIndex__returnsErrorCode();
    Container_size__afterAddingTwoElements__returnsCorrectSize();
    Container_swapElementsAtIndices__validIndices__returnsSuccess();
    Container_swapElementsAtIndices__invalidIndices__returnsErrorCode();
    Container_popElementFromEnd__whenContainerIsNotEmpty__returnsLastElementAndRemovesFromEnd();
    Container_popElementFromEnd__whenContainerIsEmpty__returnsNULL();
}

void Container_expandIfCapacityReached__whenCapacityIsZero__expandsCapacityToOne() {
    Container* container = Container_create(File_destroy);
    assert(container->capacity == 0);
    Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE);
    assert(container->capacity == 1);
    Container_destroyWithElements(container);
}

void Container_expandIfCapacityReached__whenCapacityNotZero__doublesCapacity() {
    Container* container = Container_create(File_destroy);
    assert(container->capacity == 0);
    Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE);
    assert(container->capacity == 1);
    Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE);
    assert(container->capacity == 2);
    Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE);
    assert(container->capacity == 4);
    Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE);
    Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE);
    assert(container->capacity == 8);
    Container_destroyWithElements(container);
}

void Container_pushElementToEnd__validInput__appendsElement() {
    Container* container = Container_create(File_destroy);
    assert(Container_size(container) == 0);
    assert(Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE) == 0);
    assert(Container_size(container) == 1);
    Container_destroyWithElements(container);
}

void Container_getElementAtIndex__validIndex__returnsElement() {
    Container* container = Container_create(File_destroy);
    File* file = INSTANCE_OF_GENERIC_FILE;
    Container_pushElementToEnd(container, file);
    assert(Container_getElementAtIndex(container, 0) == file);
    Container_destroyWithElements(container);
}

void Container_getElementAtIndex__invalidIndex__returnsNULL() {
    Container* container = Container_create(File_destroy);
    assert(Container_getElementAtIndex(container, 0) == NULL);
    Container_destroyWithElements(container);
}

void Container_deleteElementAtIndex__validIndex__returnsSuccess() {
    Container* container = Container_create(File_destroy);
    Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE);
    assert(Container_deleteElementAtIndex(container, 0) == 0);
    assert(Container_size(container) == 0);
    Container_destroyWithElements(container);
}

void Container_deleteElementAtIndex__invalidIndex__returnsErrorCode() {
    Container* container = Container_create(File_destroy);
    assert(Container_deleteElementAtIndex(container, 0) != 0);
    Container_destroyWithElements(container);
}

void Container_updateElementAtIndex__validIndex__returnsSuccess() {
    Container* container = Container_create(File_destroy);
    Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE);
    File* updatedFile = File_create(0, "abc", "def", 123);
    assert(Container_updateElementAtIndex(container, updatedFile, 0) == 0);
    assert(Container_getElementAtIndex(container, 0) == updatedFile);
    Container_destroyWithElements(container);
}

void Container_updateElementAtIndex__invalidIndex__returnsErrorCode() {
    Container* container = Container_create(File_destroy);
    File* file = INSTANCE_OF_GENERIC_FILE;
    assert(Container_updateElementAtIndex(container, file, 0) != 0);
    File_destroy(file);
    Container_destroyWithElements(container);
}

void Container_size__afterAddingTwoElements__returnsCorrectSize() {
    Container* container = Container_create(File_destroy);
    Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE);
    Container_pushElementToEnd(container, INSTANCE_OF_GENERIC_FILE);
    assert(Container_size(container) == 2);
    Container_destroyWithElements(container);
}

void Container_swapElementsAtIndices__validIndices__returnsSuccess() {
    Container* container = Container_create(File_destroy);
    File* first = File_create(1, "a", "a", 1);
    File* second = File_create(2, "b", "b", 2);
    Container_pushElementToEnd(container, first);
    Container_pushElementToEnd(container, second);
    assert(
        (Container_getElementAtIndex(container, 0) == first) &&
        (Container_getElementAtIndex(container, 1) == second)
    );
    assert(Container_swapElementsAtIndices(container, 0, 1) == 0);
    assert(
        (Container_getElementAtIndex(container, 1) == first) &&
        (Container_getElementAtIndex(container, 0) == second)
    );
    Container_destroyWithElements(container);
}

void Container_swapElementsAtIndices__invalidIndices__returnsErrorCode() {
    Container* container = Container_create(File_destroy);
    assert(Container_swapElementsAtIndices(container, 0, 1) != 0);
    Container_destroyWithElements(container);
}

void Container_popElementFromEnd__whenContainerIsNotEmpty__returnsLastElementAndRemovesFromEnd() {
    Container* container = Container_create(File_destroy);
    File* file = INSTANCE_OF_GENERIC_FILE;
    Container_pushElementToEnd(container, file);
    assert(Container_popElementFromEnd(container) == file);
    assert(Container_size(container) == 0);
    File_destroy(file);
    Container_destroyWithElements(container);
}

void Container_popElementFromEnd__whenContainerIsEmpty__returnsNULL() {
    Container* container = Container_create(File_destroy);
    assert(Container_popElementFromEnd(container) == NULL);
    Container_destroyWithElements(container);
}