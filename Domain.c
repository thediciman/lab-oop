#include "Domain.h"

#include <stdlib.h>
#include <string.h>

File* File_create(int archiveCatalogueNumber, char* stateOfDeterioration, char* fileType, int yearOfCreation) {
    File* createdFile = (File*) malloc(sizeof(File));
    createdFile->archiveCatalogueNumber = archiveCatalogueNumber;
    strcpy(createdFile->stateOfDeterioration, stateOfDeterioration);
    strcpy(createdFile->fileType, fileType);
    createdFile->yearOfCreation = yearOfCreation;
    return createdFile;
}

void File_destroy(File* file) {
    free(file);
}

int File_getArchiveCatalogueNumber(File* file) {
    return file->archiveCatalogueNumber;
}

char* File_getStateOfDeterioration(File* file) {
    return file->stateOfDeterioration;
}

char* File_getFileType(File* file) {
    return file->fileType;
}

int File_getYearOfCreation(File* file) {
    return file->yearOfCreation;
}

void File_setArchiveCatalogueNumber(File* file, int newArchiveCatalogueNumber) {
    file->archiveCatalogueNumber = newArchiveCatalogueNumber;
}

void File_setStateOfDeterioration(File* file, char* newStateOfDeterioration) {
    strcpy(file->stateOfDeterioration, newStateOfDeterioration);
}

void File_setFileType(File* file, char* newFileType) {
    strcpy(file->fileType, newFileType);
}

void File_setYearOfCreation(File* file, int newYearOfCreation) {
    file->yearOfCreation = newYearOfCreation;    
}