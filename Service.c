#include "Service.h"
#include "Domain.h"
#include "Container.h"
#include "Repository.h"

#include <stdlib.h>
#include <string.h>

Service* Service_create(Repository* repository) {
    Service* service = (Service*) malloc(sizeof(Service));
    service->repository = repository;
    return service;
}

void Service_destroy(Service* service) {
    free(service);
}

int Service_addFile(Service* service, int archiveCatalogueNumber, char* stateOfDeterioration, char* fileType, int yearOfCreation) {
    File* file = File_create(archiveCatalogueNumber, stateOfDeterioration, fileType, yearOfCreation);
    int returnCode = Repository_addElement(service->repository, file);
    if (returnCode != 0) {
        File_destroy(file);
    }
    return returnCode;
}

int Service_updateFile(Service* service, int archiveCatalogueNumber, char* newStateOfDeterioration, char* newFileType, int newYearOfCreation) {
    File* file = File_create(archiveCatalogueNumber, newStateOfDeterioration, newFileType, newYearOfCreation);
    int returnCode = Repository_updateElement(service->repository, file);
    if (returnCode != 0) {
        File_destroy(file);
    }
    return returnCode;
}

int Service_deleteFile(Service* service, int archiveCatalogueNumber) {
    return Repository_deleteElementWithID(service->repository, archiveCatalogueNumber);
}

Container* Service_getAllFiles(Service* service) {
    return Repository_getContainer(service->repository);
}

Container* Service_getFilesByFileType(Service* service, char* fileType) {
    Container* allFiles = Repository_getContainer(service->repository);
    Container* filteredFiles = Container_create();
    for (int i = 0; i < Container_size(allFiles); ++i) {
        if (strcmp(File_getFileType(Container_getElementAtIndex(allFiles, i)), fileType) == 0) {
            Container_pushElementToEnd(filteredFiles, Container_getElementAtIndex(allFiles, i));
        }
    }
    return filteredFiles;
}

Container* Service_getFilesByYearOfCreation(Service* service, int yearOfCreation) {
    Container* allFiles = Repository_getContainer(service->repository);
    Container* filteredFiles = Container_create();
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
