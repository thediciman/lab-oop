#include "ServiceTests.h"

#include "Service.h"
#include "Domain.h"
#include "UndoService.h"
#include "Repository.h"

#include <assert.h>
#include <string.h>

void testService() {
    Service_addFile__validFile__returnsSuccess();
    Service_addFile__invalidFile__returnsErrorCode();
    Service_updateFile__validFile__returnsSuccess();
    Service_updateFile__invalidFile__returnsErrorCode();
    Service_deleteFile__validFile__returnsSuccess();
    Service_deleteFile__invalidFile__returnsErrorCode();
    Service_getAllFiles__justWorksIGuess();
    Service_getFilesByFileType__returnsCorrectFiles();
    Service_getFilesByYearOfCreation__returnsCorrectFiles();
}

void Service_addFile__validFile__returnsSuccess() {
    Repository* repository = Repository_create();
    UndoService* undoService = UndoService_create();
    Service* service = Service_create(repository, undoService);
    assert(Service_addFile(service, 1, "blabla", "idk", 69420) == 0);
    UndoService_destroy(undoService);
    Repository_destroy(repository);
    Service_destroy(service);
}

void Service_addFile__invalidFile__returnsErrorCode() {
    Repository* repository = Repository_create();
    UndoService* undoService = UndoService_create();
    Service* service = Service_create(repository, undoService);
    Service_addFile(service, 1, "blabla", "idk", 69420);
    assert(Service_addFile(service, 1, "blabla", "idk", 69420) != 0);
    UndoService_destroy(undoService);
    Repository_destroy(repository);
    Service_destroy(service);
}

void Service_updateFile__validFile__returnsSuccess() {
    Repository* repository = Repository_create();
    UndoService* undoService = UndoService_create();
    Service* service = Service_create(repository, undoService);
    Service_addFile(service, 1, "blabla", "idk", 69420);
    assert(Service_updateFile(service, 1, "new", "old", 42069) == 0);
    UndoService_destroy(undoService);
    Repository_destroy(repository);
    Service_destroy(service);
}

void Service_updateFile__invalidFile__returnsErrorCode() {
    Repository* repository = Repository_create();
    UndoService* undoService = UndoService_create();
    Service* service = Service_create(repository, undoService);
    assert(Service_updateFile(service, 1, "new", "old", 42069) != 0);
    UndoService_destroy(undoService);
    Repository_destroy(repository);
    Service_destroy(service);
}

void Service_deleteFile__validFile__returnsSuccess() {
    Repository* repository = Repository_create();
    UndoService* undoService = UndoService_create();
    Service* service = Service_create(repository, undoService);
    Service_addFile(service, 1, "blabla", "idk", 69420);
    assert(Service_deleteFile(service, 1) == 0);
    UndoService_destroy(undoService);
    Repository_destroy(repository);
    Service_destroy(service);
}

void Service_deleteFile__invalidFile__returnsErrorCode() {
    Repository* repository = Repository_create();
    UndoService* undoService = UndoService_create();
    Service* service = Service_create(repository, undoService);
    assert(Service_deleteFile(service, 1) != 0);
    UndoService_destroy(undoService);
    Repository_destroy(repository);
    Service_destroy(service);
}

void Service_getAllFiles__justWorksIGuess() {
    Repository* repository = Repository_create();
    UndoService* undoService = UndoService_create();
    Service* service = Service_create(repository, undoService);
    assert(Service_getAllFiles(service) == Repository_getContainer(repository));
    UndoService_destroy(undoService);
    Repository_destroy(repository);
    Service_destroy(service);
}

void Service_getFilesByFileType__returnsCorrectFiles() {
    Repository* repository = Repository_create();
    UndoService* undoService = UndoService_create();
    Service* service = Service_create(repository, undoService);
    Service_addFile(service, 1, "abc", "aaa", 100);
    Service_addFile(service, 2, "acb", "bbb", 200);
    Service_addFile(service, 3, "bca", "aaa", 300);
    Container* filteredFiles = Service_getFilesByFileType(service, "aaa");
    for (int i = 0; i < Container_size(filteredFiles); ++i) {
        assert(strcmp(File_getFileType(Container_getElementAtIndex(filteredFiles, i)), "aaa") == 0);
    }
    Container_destroyWithoutElements(filteredFiles);
    UndoService_destroy(undoService);
    Repository_destroy(repository);
    Service_destroy(service);
}

void Service_getFilesByYearOfCreation__returnsCorrectFiles() {
    Repository* repository = Repository_create();
    UndoService* undoService = UndoService_create();
    Service* service = Service_create(repository, undoService);
    Service_addFile(service, 1, "abc", "aaa", 100);
    Service_addFile(service, 2, "acb", "bbb", 200);
    Service_addFile(service, 3, "bca", "aaa", 300);
    Container* filteredFiles = Service_getFilesByYearOfCreation(service, 250);
    for (int i = 0; i < Container_size(filteredFiles); ++i) {
        assert(File_getYearOfCreation(Container_getElementAtIndex(filteredFiles, i)) < 250);
    }
    Container_destroyWithoutElements(filteredFiles);
    UndoService_destroy(undoService);
    Repository_destroy(repository);
    Service_destroy(service);
}