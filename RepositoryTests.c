#include "RepositoryTests.h"

#include "Domain.h"
#include "Repository.h"

#include <assert.h>
#include <stdlib.h>

#define INSTANCE_OF_GENERIC_FILE File_create(0, "", "", 0)

void testRepository() {
    Repository_indexOfElement__invalidElement__returnsErrorCode();
    Repository_indexOfElement__validElement__returnsCorrectIndex();
    Repository_addElement__validElement__returnsSuccess();
    Repository_addElement__duplicateElement__returnsErrorCode();
    Repository_deleteElement__validElement__returnsSuccess();
    Repository_deleteElement__invalidElement__returnsErrorCode();
    Repository_deleteElementWithID__validID__returnsSuccess();
    Repository_deleteElementWithID__invalidID__returnsErrorCode();
    Repository_updateElement__validElement__returnsSuccess();
    Repository_updateElement__invalidElement__returnsErrorCode();
    Repository_getContainer__returnsContainerDUHHHH();
    Repository_replaceContainer__replacesContainer();
    Repository_getFileByID__validID__returnsFile();
    Repository_getFileByID__invalidID__returnsNULL();
}

void Repository_indexOfElement__invalidElement__returnsErrorCode() {
    Repository* repository = Repository_create();
    assert(Repository_indexOfElement(repository, 0) == -1);
    Repository_destroy(repository);
}

void Repository_indexOfElement__validElement__returnsCorrectIndex() {
    Repository* repository = Repository_create();
    File* file = INSTANCE_OF_GENERIC_FILE;
    Repository_addElement(repository, file);
    assert(Repository_indexOfElement(repository, file) == 0);
    Repository_destroy(repository);
}

void Repository_addElement__validElement__returnsSuccess() {
    Repository* repository = Repository_create();
    assert(Repository_addElement(repository, INSTANCE_OF_GENERIC_FILE) == 0);
    Repository_destroy(repository);
}

void Repository_addElement__duplicateElement__returnsErrorCode() {
    Repository* repository = Repository_create();
    assert(Repository_addElement(repository, INSTANCE_OF_GENERIC_FILE) == 0);
    File* otherFile = INSTANCE_OF_GENERIC_FILE;
    assert(Repository_addElement(repository, otherFile) != 0);
    File_destroy(otherFile);
    Repository_destroy(repository);
}

void Repository_deleteElement__validElement__returnsSuccess() {
    Repository* repository = Repository_create();
    File* file = INSTANCE_OF_GENERIC_FILE;
    Repository_addElement(repository, file);
    assert(Repository_deleteElement(repository, file) == 0);
    Repository_destroy(repository);
}

void Repository_deleteElement__invalidElement__returnsErrorCode() {
    Repository* repository = Repository_create();
    File* file = INSTANCE_OF_GENERIC_FILE;
    assert(Repository_deleteElement(repository, file) != 0);
    File_destroy(file);
    Repository_destroy(repository);
}

void Repository_deleteElementWithID__validID__returnsSuccess() {
    Repository* repository = Repository_create();
    File* file = INSTANCE_OF_GENERIC_FILE;
    Repository_addElement(repository, file);
    assert(Repository_deleteElementWithID(repository, 0) == 0);
    Repository_destroy(repository);
}

void Repository_deleteElementWithID__invalidID__returnsErrorCode() {
    Repository* repository = Repository_create();
    assert(Repository_deleteElementWithID(repository, 0) != 0);
    Repository_destroy(repository);
}

void Repository_updateElement__validElement__returnsSuccess() {
    Repository* repository = Repository_create();
    Repository_addElement(repository, INSTANCE_OF_GENERIC_FILE);
    File* otherFile = File_create(0, "abc", "def", 2);
    assert(Repository_updateElement(repository, otherFile) == 0);
    assert(Repository_getFileByID(repository, 0) == otherFile);
    Repository_destroy(repository);
}

void Repository_updateElement__invalidElement__returnsErrorCode() {
    Repository* repository = Repository_create();
    File* file = INSTANCE_OF_GENERIC_FILE;
    assert(Repository_updateElement(repository, file) != 0);
    File_destroy(file);
    Repository_destroy(repository);
}

void Repository_getContainer__returnsContainerDUHHHH() {
    Repository* repository = Repository_create();
    assert(Repository_getContainer(repository) == repository->container);
    Repository_destroy(repository);
}

void Repository_replaceContainer__replacesContainer() {
    Repository* repository = Repository_create();
    Container* otherContainer = Container_create(File_destroy);
    Repository_replaceContainer(repository, otherContainer);
    assert(Repository_getContainer(repository) == otherContainer);
    Repository_destroy(repository);
}

void Repository_getFileByID__validID__returnsFile() {
    Repository* repository = Repository_create();
    File* file = INSTANCE_OF_GENERIC_FILE;
    Repository_addElement(repository, file);
    assert(Repository_getFileByID(repository, 0) == file);
    Repository_destroy(repository);
}

void Repository_getFileByID__invalidID__returnsNULL() {
    Repository* repository = Repository_create();
    assert(Repository_getFileByID(repository, 0) == NULL);
    Repository_destroy(repository);
}