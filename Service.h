#pragma once

#include "UndoService.h"
#include "Repository.h"
#include "macros.h"

typedef struct {
    void* undoService;
    Repository* repository;
} Service;

typedef int (*FilterFunction) (File*);
typedef int (*ComparatorFunction) (File*, File*);

char GLOBAL_FILETYPE_FILTER[MAX_CHAR_LEN];
int GLOBAL_YEAR_OF_CREATION_FILTER;

/*
    Description:
        - Creates a new dynamically allocated Service and returns it.
    Inputs:
        - repository: The repository that will be managed by the service.
        - undoService: The service that will handle the undo/redo operations.
    Outputs:
        - The newly allocated Service.
*/
Service* Service_create(Repository* repository, void* undoService);

/*
    Description:
        - Destroys a service.
    Inputs:
        - service: The service to be destroyed.
    Outputs:
        - None.
*/
void Service_destroy(Service* service);

/*
    Description:
        - Adds a file to the internal repository, given the file's attributes, and updates the undoService.
    Inputs:
        - service: The service in which the file will be created and added.
        - archiveCatalogueNumber, stateOfDeterioration, fileType, yearOfCreation: data defining the File to be added.
    Outputs:
        - The return code of Repository_addElement, which is:
            - 0 on success, -4 if there already exists an element with that ID or whatever Container_expandIfCapacityReached returns otherwise.
*/
int Service_addFile(Service* service, int archiveCatalogueNumber, char* stateOfDeterioration, char* fileType, int yearOfCreation);

/*
    Description:
        - Updates a file from the service's internal repository, and updates the undoService.
    Inputs:
        - service: The service in which the file will be updated.
        - archiveCatalogueNumber, stateOfDeterioration, fileType, yearOfCreation: data defining the File to be updated.
    Outputs:
        - The return code of Repository_updateElement, which is:
            - 0 on success, -5 if the element was not found.
*/
int Service_updateFile(Service* service, int archiveCatalogueNumber, char* newStateOfDeterioration, char* newFileType, int newYearOfCreation);

/*
    Description:
        - Deletes a file having a given ID from the service's repository.
    Inputs:
        - service: The service on which we perform the deletion.
        - archiveCatalogueNumber: the ID of the element which we want to delete.
    Outputs:
        - The return code of Repository_deleteElement, which is:
            - 0 on success, -5 if the element was not found.
*/
int Service_deleteFile(Service* service, int archiveCatalogueNumber);

/*
    Description:
        - Returns a Container which contains all files from the service's repository.
    Inputs:
        - service: The service from which we retrieve all the files.
    Outputs:
        - A container which has all the files.
*/
Container* Service_getAllFiles(Service* service);

/*
    Description:
        - Returns a Container with all files of a given fileType from the service's repository.
    Inputs:
        - service: The service from which we retrieve the filtered files.
        - fileType: the fileType used to filter the files.
    Outputs:
        - A container which has all the filtered files, by fileType.
*/
Container* Service_getFilesByFileType(Service* service, char* fileType);

/*
    Description:
        - Returns a Container with all files which have the yearOfCreation less than a given value, sorted ascendingly.
    Inputs:
        - service: The service from which we retrieve the filtered files.
        - yearOfCreation: the value used to filter the files by yearOfCreation.
    Outputs:
        - A container which has all the filtered files by yearOfCreation, sorted ascendingly.
*/
Container* Service_getFilesByYearOfCreation(Service* service, int yearOfCreation);

/*
    Description:
        - Performs an undo of the last operation.
    Inputs:
        - service: The service on which we perform the undo operation.
    Outputs:
        - 0 on success, -6 if there was no possible undo operation.
*/
int Service_undoLastOperation(Service* service);

/*
    Description:
        - Performs an redo of the last operation.
    Inputs:
        - service: The service on which we perform the redo operation.
    Outputs:
        - 0 on success, -6 if there was no possible redo operation.
*/
int Service_redoLastOperation(Service* service);

/*
    Description:
        - Returns a container of objects, filtered using a given filtering function.
    Inputs:
        - service: the service whose files we want to filter.
        - filter: the function used to filter the files.
    Outputs:
        - The container which has the desired filtered files.
*/
Container* Service_filterFilesByFilter(Service* service, FilterFunction filter);

/*
    Description:
        - Sorts in-place and also returns a container, given a comparator function.
    Inputs:
        - container: the container to be sorted.
        - comparator: the function used to compare two elements.
    Outputs:
        - The sorted container.
*/
Container* Service_sortFilesByComparator(Container* container, ComparatorFunction comparator);

/*
    Description:
        - Predicate function used to filter files, by fileType.
        - It requires GLOBAL_FILETYPE_FILTER to be set before using the function for filtering.
    Inputs:
        - file: the file which is checked for filtering.
    Outputs:
        - 1 if the file shall be kept, 0 otherwise.
*/
int filterByFiletype(File* file);

/*
    Description:
        - Predicate function used to filter files, by yearOfCreation.
        - It requires GLOBAL_YEAR_OF_CREATION to be set before using the function for filtering.
    Inputs:
        - file: the file which is checked for filtering.
    Outputs:
        - 1 if the file shall be kept, 0 otherwise.
*/
int filterByYearOfCreation(File* file);

/*
    Description:
        - Function that determines the order between two elements;
        - The order which it imposes is that the first file's stateOfDeterioration is greater lexicographically than the second file.
    Inputs:
        - first, second: the files to be compared.
    Outputs:
        - 1 if the files are in the correct order, 0 otherwise.
*/
int compareStateOfDeterioration_Greater(File* first, File* second);

/*
    Description:
        - Function that determines the order between two elements;
        - The order which it imposes is that the first file's stateOfDeterioration is less lexicographically than the second file.
    Inputs:
        - first, second: the files to be compared.
    Outputs:
        - 1 if the files are in the correct order, 0 otherwise.
*/
int compareStateOfDeterioration_Less(File* first, File* second);