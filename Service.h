#pragma once

#include "UndoService.h"
#include "Repository.h"

typedef struct {
    UndoService* undoService;
    Repository* repository;
} Service;

Service* Service_create(Repository* repository, UndoService* undoService);

void Service_destroy(Service* service);

int Service_addFile(Service* service, int archiveCatalogueNumber, char* stateOfDeterioration, char* fileType, int yearOfCreation);

int Service_updateFile(Service* service, int archiveCatalogueNumber, char* newStateOfDeterioration, char* newFileType, int newYearOfCreation);

int Service_deleteFile(Service* service, int archiveCatalogueNumber);

Container* Service_getAllFiles(Service* service);

Container* Service_getFilesByFileType(Service* service, char* fileType);

Container* Service_getFilesByYearOfCreation(Service* service, int yearOfCreation);