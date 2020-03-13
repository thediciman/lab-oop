#include "Repository.h"

#include <stdlib.h>

Repository* Repository_create() {
    Repository* repository = (Repository*) malloc(sizeof(Repository));
    repository->container = Container_create(File_destroy);
    return repository;
}

void Repository_destroy(Repository* repository) {
    Container_destroyWithElements(repository->container);
    free(repository);
}

int Repository_indexOfElement(Repository* repository, File* element) {
    for (int i = 0; i < Container_size(repository->container); ++i) {
        if (File_getArchiveCatalogueNumber(Container_getElementAtIndex(repository->container, i)) == File_getArchiveCatalogueNumber(element)) {
            return i;
        }
    }
    return -1;
}

int Repository_addElement(Repository* repository, File* element) {
    if (Repository_indexOfElement(repository, element) != -1) {
        return -4;
    }
    return Container_pushElementToEnd(repository->container, element);
}

int Repository_deleteElement(Repository* repository, File* element) {
    int indexOfElement = Repository_indexOfElement(repository, element);
    if (indexOfElement == -1) {
        return -5;
    }
    return Container_deleteElementAtIndex(repository->container, indexOfElement);
}

int Repository_deleteElementWithID(Repository* repository, int ID) {
    for (int i = 0; i < Container_size(repository->container); ++i) {
        if (File_getArchiveCatalogueNumber(Container_getElementAtIndex(repository->container, i)) == ID) {
            return Repository_deleteElement(repository, Container_getElementAtIndex(repository->container, i));
        }
    }
    return -5;
}

int Repository_updateElement(Repository* repository, File* element) {
    int indexOfElement = Repository_indexOfElement(repository, element);
    if (indexOfElement == -1) {
        return -5;
    }
    return Container_updateElementAtIndex(repository->container, element, indexOfElement);
}

Container* Repository_getContainer(Repository* repository) {
    return repository->container;
}

void Repository_replaceContainer(Repository* repository, Container* previousState) {
    Container_destroyWithElements(repository->container);
    repository->container = previousState;
}