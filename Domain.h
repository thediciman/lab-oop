#pragma once

#include "macros.h"

typedef struct {
    int archiveCatalogueNumber;
    char stateOfDeterioration[MAX_CHAR_LEN];
    char fileType[MAX_CHAR_LEN];
    int yearOfCreation;
} File;

/*
    Description:
        - Creates a new dynamically allocated File and returns it.
    Inputs:
        - archiveCatalogueNumber, stateOfDeterioration, fileType, yearOfCreation: data that defines the File.
    Outputs:
        - The newly allocated File.
*/
File* File_create(int archiveCatalogueNumber, char* stateOfDeterioration, char* fileType, int yearOfCreation);

/*
    Description:
        - Deallocates the memory used by a File.
    Inputs:
        - file: pointer to the File that should be destroyed.
    Outputs:
        - None.
*/
void File_destroy(void* file);

/*
    Description:
        - Returns the archiveCatalogueNumber of a File.
    Inputs:
        - file: pointer to the File that we want to get the archiveCatalogueNumber from.
    Outputs:
        - The archiveCatalogueNumber.
*/
int File_getArchiveCatalogueNumber(File* file);

/*
    Description:
        - Returns the stateOfDeterioration of a File.
    Inputs:
        - file: pointer to the File that we want to get the stateOfDeterioration from.
    Outputs:
        - The stateOfDeterioration.
*/
char* File_getStateOfDeterioration(File* file);

/*
    Description:
        - Returns the fileType of a File.
    Inputs:
        - file: pointer to the File that we want to get the fileType from.
    Outputs:
        - The fileType.
*/
char* File_getFileType(File* file);

/*
    Description:
        - Returns the yearOfCreation of a File.
    Inputs:
        - file: pointer to the File that we want to get the yearOfCreation from.
    Outputs:
        - The yearOfCreation.
*/
int File_getYearOfCreation(File* file);

/*
    Description:
        - Updates the archiveCatalogueNumber of a File.
    Inputs:
        - file: pointer to the File whose yearOfCreation we want to update.
    Outputs:
        - None.
*/
void File_setArchiveCatalogueNumber(File* file, int newArchiveCatalogueNumber);

/*
    Description:
        - Updates the stateOfDeterioration of a File.
    Inputs:
        - file: pointer to the File whose stateOfDeterioration we want to update.
    Outputs:
        - None.
*/
void File_setStateOfDeterioration(File* file, char* newStateOfDeterioration);

/*
    Description:
        - Updates the fileType of a File.
    Inputs:
        - file: pointer to the File whose fileType we want to update.
    Outputs:
        - None.
*/
void File_setFileType(File* file, char* newFileType);

/*
    Description:
        - Updates the yearOfCreation of a File.
    Inputs:
        - file: pointer to the File whose yearOfCreation we want to update.
    Outputs:
        - None.
*/
void File_setYearOfCreation(File* file, int newYearOfCreation);