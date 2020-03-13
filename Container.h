#pragma once

typedef void* TElem;

typedef void (*DestroyElementFunction) (void*);

typedef struct {
    TElem* data;
    int size;
    int capacity;
    DestroyElementFunction destroyFunction;
} Container;

/*
    Description:
        - Creates a new dynamically allocated Container and returns it.
    Inputs:
        - destroyFunction: Pointer to a function that can destroy an element stored in the container.
    Outputs:
        - The newly allocated Container.
*/
Container* Container_create(DestroyElementFunction destroyFunction);

/*
    Description:
        - Destroys a container, while also destroying its elements.
    Inputs:
        - container: The container to be destroyed.
    Outputs:
        - None.
*/
void Container_destroyWithElements(void* container);

/*
    Description:
        - Destroys a container, without destroying its elements.
    Inputs:
        - container: The container to be destroyed.
    Outputs:
        - None.
*/
void Container_destroyWithoutElements(void* container);

/*
    Description:
        - Checks if the capacity of the container has been reached, and expands the container if so.
    Inputs:
        - container: The container to be checked and expanded.
    Outputs:
        - 0 on success, -1 if the container could not be expanded.
*/
int Container_expandIfCapacityReached(Container* container);

/*
    Description:
        - Adds an element to the end of a container.
    Inputs:
        - container: The container to which we add the element to.
        - element: The element to be added.
    Outputs:
        - 0 on success, or whatever Container_expandIfCapacityReached returns otherwise.
*/
int Container_pushElementToEnd(Container* container, TElem element);

/*
    Description:
        - Retrieves an element from a container, at a given index.
    Inputs:
        - container: The container from which we want to retrieve the element.
        - index: The index from which the element should be retrieved.
    Outputs:
        - NULL if the index is invalid, the required element on success.
*/
TElem Container_getElementAtIndex(Container* container, int index);

/*
    Description:
        - Destroys and removes an element at an index from a container.
    Inputs:
        - container: The container from which the element should be deleted.
        - index: The index at which the element should be deleted.
    Outputs:
        - 0 on success, -2 if the index is invalid.
*/
int Container_deleteElementAtIndex(Container* container, int index);

/*
    Description:
        - Destroys an element at a given index from a container and overwrites it with a new one.
    Inputs:
        - container: The container on which we want to perform the update.
        - element: The element to overwrite the old element with.
        - index: The index of the element to be overwritten.
    Outputs:
        - 0 on success, -2 if the index is invalid.
*/
int Container_updateElementAtIndex(Container* container, TElem element, int index);

/*
    Description:
        - Gets the size of a container.
    Inputs:
        - container: The container whose size we want to get.
    Outputs:
        - The size of the container.
*/
int Container_size(Container* container);

/*
    Description:
        - Swap two elements inside a container, given two indices.
    Inputs:
        - container: The container whose elements we want to swap.
        - firstIndex, secondIndex: the indices of the elements to be swapped.
    Outputs:
        - 0 on success, -2 if either of the indices is invalid.
*/
int Container_swapElementsAtIndices(Container* container, int firstIndex, int secondIndex);

/*
    Description:
        - Removes and returns the last element from a container.
    Inputs:
        - container: The container from which we want to pop the last element.
    Outputs:
        - The popped element, or NULL if the container is empty.
*/
TElem Container_popElementFromEnd(Container* container);

/*
    Description:
        - Returns the DestroyElementFunction of a container.
    Inputs:
        - container: The container from which we want to get the DestroyElementFunction.
    Outputs:
        - The DestroyElementFunction of the container.
*/
DestroyElementFunction Container_getDestroyElementFunction(Container* container);