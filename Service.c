#include "Service.h"
#include "Domain.h"
#include "Container.h"
#include "Repository.h"

#include <stdlib.h>
#include <string.h>

Service* Service_create(Repository* repository, UndoService* undoService) {
    Service* service = (Service*) malloc(sizeof(Service));
    service->repository = repository;
    service->undoService = undoService;
    return service;
}

void Service_destroy(Service* service) {
    free(service);
}

int Service_addFile(Service* service, int archiveCatalogueNumber, char* stateOfDeterioration, char* fileType, int yearOfCreation) {
    File* file = File_create(archiveCatalogueNumber, stateOfDeterioration, fileType, yearOfCreation);
    Container* deepCopyOfData = Repository_getDeepCopyOfData(service->repository);
    int returnCode = Repository_addElement(service->repository, file);
    if (returnCode != 0) {
        File_destroy(file);
        Container_destroyWithElements(deepCopyOfData);
        return returnCode;
    }
    UndoService_addToHistory(service->undoService, deepCopyOfData);
    return 0;
}

int Service_updateFile(Service* service, int archiveCatalogueNumber, char* newStateOfDeterioration, char* newFileType, int newYearOfCreation) {
    File* file = File_create(archiveCatalogueNumber, newStateOfDeterioration, newFileType, newYearOfCreation);
    Container* deepCopyOfData = Repository_getDeepCopyOfData(service->repository);
    int returnCode = Repository_updateElement(service->repository, file);
    if (returnCode != 0) {
        File_destroy(file);
        Container_destroyWithElements(deepCopyOfData);
        return returnCode;
    }
    UndoService_addToHistory(service->undoService, deepCopyOfData);
    return 0;
}

int Service_deleteFile(Service* service, int archiveCatalogueNumber) {
    Container* deepCopyOfData = Repository_getDeepCopyOfData(service->repository);
    int returnCode = Repository_deleteElementWithID(service->repository, archiveCatalogueNumber);
    if (returnCode != 0) {
        Container_destroyWithElements(deepCopyOfData);
        return returnCode;
    }
    UndoService_addToHistory(service->undoService, deepCopyOfData);
    return 0;
}

Container* Service_getAllFiles(Service* service) {
    return Repository_getContainer(service->repository);
}

Container* Service_getFilesByFileType(Service* service, char* fileType) {
    Container* allFiles = Repository_getContainer(service->repository);
    Container* filteredFiles = Container_create(File_destroy);
    for (int i = 0; i < Container_size(allFiles); ++i) {
        if (strcmp(File_getFileType(Container_getElementAtIndex(allFiles, i)), fileType) == 0) {
            Container_pushElementToEnd(filteredFiles, Container_getElementAtIndex(allFiles, i));
        }
    }
    return filteredFiles;
}

Container* Service_getFilesByYearOfCreation(Service* service, int yearOfCreation) {
    Container* allFiles = Repository_getContainer(service->repository);
    Container* filteredFiles = Container_create(File_destroy);
    for (int i = 0; i < Container_size(allFiles); ++i) {
        if (File_getYearOfCreation(Container_getElementAtIndex(allFiles, i)) < yearOfCreation) {
            Container_pushElementToEnd(filteredFiles, Container_getElementAtIndex(allFiles, i));
        }
    }
    int sorted = 0;
    do {
        sorted = 1;
        for (int i = 0; i < Container_size(filteredFiles) - 1; ++i) {
            if (File_getYearOfCreation(Container_getElementAtIndex(filteredFiles, i)) > File_getYearOfCreation(Container_getElementAtIndex(filteredFiles, i + 1))) {
                Container_swapElementsAtIndices(filteredFiles, i, i + 1);
                sorted = 0;
            }
        }
    } while (sorted == 0);
    return filteredFiles;
}

int Service_undoLastOperation(Service* service) {
    Container* previousState = UndoService_popFromHistory(service->undoService);
    if (previousState == NULL) {
        return -6;
    }
    Repository_replaceContainer(service->repository, previousState);
    return 0;
}