#include "Service.h"
#include "Domain.h"
#include "Container.h"
#include "Repository.h"
#include "Utils.h"
#include "macros.h"
#include "BonusUndoService.h"

#include <stdlib.h>
#include <string.h>

typedef int (*FilterFunction) (File*);
typedef int (*ComparatorFunction) (File*, File*);

char GLOBAL_FILETYPE_FILTER[MAX_CHAR_LEN];
int GLOBAL_YEAR_OF_CREATION_FILTER;

int filterByFiletype(File* file) {
    return strcmp(File_getFileType(file), GLOBAL_FILETYPE_FILTER) == 0;
}

int filterByYearOfCreation(File* file) {
    return File_getYearOfCreation(file) < GLOBAL_YEAR_OF_CREATION_FILTER;
}

int compareYearOfCreation_Greater(File* first, File* second) {
    return File_getYearOfCreation(first) > File_getYearOfCreation(second);
}

int compareYearOfCreation_Less(File* first, File* second) {
    return File_getYearOfCreation(first) < File_getYearOfCreation(second);
}

Service* Service_create(Repository* repository, void* undoService) {
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
#ifndef BONUS_UNDO_SERVICE
    Container* deepCopyOfData = Utils_getDeepCopyOfFileContainer(Repository_getContainer(service->repository));
#endif
    int returnCode = Repository_addElement(service->repository, file);
    if (returnCode != 0) {
        File_destroy(file);
#ifndef BONUS_UNDO_SERVICE
        Container_destroyWithElements(deepCopyOfData);
#endif
        return returnCode;
    }
#ifndef BONUS_UNDO_SERVICE
    UndoService_addToHistory(service->undoService, deepCopyOfData, Repository_getContainer(service->repository));
#else
    if (((BonusUndoService*) service->undoService)->duringOperation == 0) {
        FunctionCall* undoFunction = FunctionCall_create(
            NULL,
            Service_deleteFile, 
            ParameterList_create(
                service,
                archiveCatalogueNumber,
                "",
                "",
                -1
            )
        );
        FunctionCall* redoFunction = FunctionCall_create(
            Service_addFile, 
            NULL,
            ParameterList_create(
                service,
                archiveCatalogueNumber,
                stateOfDeterioration,
                fileType,
                yearOfCreation
            )
        );
        BonusUndoService_recordOperation(service->undoService, Operation_create(undoFunction, redoFunction));
    }
#endif
    return 0;
}

int Service_updateFile(Service* service, int archiveCatalogueNumber, char* newStateOfDeterioration, char* newFileType, int newYearOfCreation) {
#ifdef BONUS_UNDO_SERVICE
    File* updatedFile = NULL;
    char updatedFileStateOfDeterioration[MAX_CHAR_LEN];
    char updatedFileFileType[MAX_CHAR_LEN];
    int updatedFileYearOfCreation;
    if (((BonusUndoService*) service->undoService)->duringOperation == 0) {
        updatedFile = Repository_getFileByID(service->repository, archiveCatalogueNumber);
        strcpy(updatedFileStateOfDeterioration, File_getStateOfDeterioration(updatedFile));
        strcpy(updatedFileFileType, File_getFileType(updatedFile));
        updatedFileYearOfCreation = File_getYearOfCreation(updatedFile);
    }
#endif
    File* file = File_create(archiveCatalogueNumber, newStateOfDeterioration, newFileType, newYearOfCreation);
#ifndef BONUS_UNDO_SERVICE
    Container* deepCopyOfData = Utils_getDeepCopyOfFileContainer(Repository_getContainer(service->repository));
#endif
    int returnCode = Repository_updateElement(service->repository, file);
    if (returnCode != 0) {
        File_destroy(file);
#ifndef BONUS_UNDO_SERVICE
        Container_destroyWithElements(deepCopyOfData);
#endif
        return returnCode;
    }
#ifndef BONUS_UNDO_SERVICE
    UndoService_addToHistory(service->undoService, deepCopyOfData, Repository_getContainer(service->repository));
#else
    if (((BonusUndoService*) service->undoService)->duringOperation == 0) {
        FunctionCall* undoFunction = FunctionCall_create(
            Service_updateFile,
            NULL,
            ParameterList_create(
                service,
                archiveCatalogueNumber,
                updatedFileStateOfDeterioration,
                updatedFileFileType,
                updatedFileYearOfCreation
            )
        );
        FunctionCall* redoFunction = FunctionCall_create(
            Service_updateFile,
            NULL,
            ParameterList_create(
                service,
                archiveCatalogueNumber,
                newStateOfDeterioration,
                newFileType,
                newYearOfCreation
            )
        );
        BonusUndoService_recordOperation(service->undoService, Operation_create(undoFunction, redoFunction));
    }
#endif
    return 0;
}

int Service_deleteFile(Service* service, int archiveCatalogueNumber) {
#ifdef BONUS_UNDO_SERVICE
    File* deletedFile = NULL;
    char deletedFileStateOfDeterioration[MAX_CHAR_LEN];
    char deletedFileFileType[MAX_CHAR_LEN];
    int deletedFileYearOfCreation;
    if (((BonusUndoService*) service->undoService)->duringOperation == 0) {
        deletedFile = Repository_getFileByID(service->repository, archiveCatalogueNumber);
        strcpy(deletedFileStateOfDeterioration, File_getStateOfDeterioration(deletedFile));
        strcpy(deletedFileFileType, File_getFileType(deletedFile));
        deletedFileYearOfCreation = File_getYearOfCreation(deletedFile);
    }
#endif
#ifndef BONUS_UNDO_SERVICE
    Container* deepCopyOfData = Utils_getDeepCopyOfFileContainer(Repository_getContainer(service->repository));
#endif
    int returnCode = Repository_deleteElementWithID(service->repository, archiveCatalogueNumber);
    if (returnCode != 0) {
#ifndef BONUS_UNDO_SERVICE
        Container_destroyWithElements(deepCopyOfData);
#endif
        return returnCode;
    }
#ifndef BONUS_UNDO_SERVICE
    UndoService_addToHistory(service->undoService, deepCopyOfData, Repository_getContainer(service->repository));
#else
    if (((BonusUndoService*) service->undoService)->duringOperation == 0) {
        FunctionCall* undoFunction = FunctionCall_create(
            Service_addFile, 
            NULL,
            ParameterList_create(
                service,
                archiveCatalogueNumber,
                deletedFileStateOfDeterioration,
                deletedFileFileType,
                deletedFileYearOfCreation
            )
        );
        FunctionCall* redoFunction = FunctionCall_create(
            NULL,
            Service_deleteFile, 
            ParameterList_create(
                service,
                archiveCatalogueNumber,
                "",
                "",
                -1
            )
        );
        BonusUndoService_recordOperation(service->undoService, Operation_create(undoFunction, redoFunction));
    }
#endif
    return 0;
}

Container* Service_getAllFiles(Service* service) {
    return Repository_getContainer(service->repository);
}

Container* Service_filterFilesByFilter(Service* service, FilterFunction filter) {
    Container* allFiles = Repository_getContainer(service->repository);
    Container* filteredFiles = Container_create(File_destroy);
    for (int i = 0; i < Container_size(allFiles); ++i) {
        if (filter(Container_getElementAtIndex(allFiles, i))) {
            Container_pushElementToEnd(filteredFiles, Container_getElementAtIndex(allFiles, i));
        }
    }
    return filteredFiles;
}

Container* Service_sortFilesByComparator(Container* container, ComparatorFunction comparator) {
    int sorted = 0;
    do {
        sorted = 1;
        for (int i = 0; i < Container_size(container) - 1; ++i) {
            if (comparator(Container_getElementAtIndex(container, i), Container_getElementAtIndex(container, i + 1))) {
                Container_swapElementsAtIndices(container, i, i + 1);
                sorted = 0;
            }
        }
    } while (sorted == 0);
    return container;
}

Container* Service_getFilesByFileType(Service* service, char* fileType) {
    strcpy(GLOBAL_FILETYPE_FILTER, fileType);
    return Service_filterFilesByFilter(service, filterByFiletype);
}

Container* Service_getFilesByYearOfCreation(Service* service, int yearOfCreation) {
    GLOBAL_YEAR_OF_CREATION_FILTER = yearOfCreation;
    return Service_sortFilesByComparator(Service_filterFilesByFilter(service, filterByYearOfCreation), compareYearOfCreation_Greater);
}

int Service_undoLastOperation(Service* service) {
#ifndef BONUS_UNDO_SERVICE
   Container* previousState = UndoService_undo(service->undoService);
    if (previousState == NULL) {
        return -6;
    }
    Repository_replaceContainer(service->repository, previousState);
#else
    BonusUndoService_undo(service->undoService);
#endif
    return 0;
}

int Service_redoLastOperation(Service* service) {
#ifndef BONUS_UNDO_SERVICE
    Container* previousState = UndoService_redo(service->undoService);
    if (previousState == NULL) {
        return -6;
    }
    Repository_replaceContainer(service->repository, previousState);
#else
    BonusUndoService_redo(service->undoService);
#endif
    return 0;
}