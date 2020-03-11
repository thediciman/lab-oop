#pragma once

#define MAX_CHAR_LEN 2048

typedef struct {
    int archiveCatalogueNumber;
    char stateOfDeterioration[MAX_CHAR_LEN];
    char fileType[MAX_CHAR_LEN];
    int yearOfCreation;
} File;

File* File_create(int archiveCatalogueNumber, char* stateOfDeterioration, char* fileType, int yearOfCreation);

void File_destroy(void* file);

int File_getArchiveCatalogueNumber(File* file);

char* File_getStateOfDeterioration(File* file);

char* File_getFileType(File* file);

int File_getYearOfCreation(File* file);

void File_setArchiveCatalogueNumber(File* file, int newArchiveCatalogueNumber);

void File_setStateOfDeterioration(File* file, char* newStateOfDeterioration);

void File_setFileType(File* file, char* newFileType);

void File_setYearOfCreation(File* file, int newYearOfCreation);