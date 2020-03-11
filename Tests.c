// #include "Tests.h"

// #include "Domain.h"
// #include "Container.h"
// #include "Repository.h"
// #include "Service.h"

// #include <stdio.h>
// #include <assert.h>
// #include <string.h>

// void runAllTests() {
//     testDomain();
//     testContainer();
//     testRepository();
//     testService();
//     printf("All tests passed!\n");
// }

// void testDomain() {
//     printf("Testing the domain...\n");
    
//     File* file = createFile(12, "state", "garbage", 2020);
    
//     assert(getArchiveCatalogueNumber(file) == 12);
//     assert(getYearOfCreation(file) == 2020);
//     assert(strcmp(getStateOfDeterioration(file), "state") == 0);
//     assert(strcmp(getFileType(file), "garbage") == 0);

//     setArchiveCatalogueNumber(file, 123);
//     assert(getArchiveCatalogueNumber(file) == 123);

//     setYearOfCreation(file, 1234);
//     assert(getYearOfCreation(file) == 1234);

//     setStateOfDeterioration(file, "nono");
//     assert(strcmp(getStateOfDeterioration(file), "nono") == 0);

//     setFileType(file, "filefile");
//     assert(strcmp(getFileType(file), "filefile") == 0);

//     destroyFile(file);
// }

// void testContainer() {
//     printf("Testing the container...\n");

//     Container* container = createContainer();

//     assert(containerSize(container) == 0);
//     assert(getElementFromContainerAtIndex(container, 0) == NULL);

//     TElem* element = createFile(12, "state", "garbage", 2020);
//     assert(pushElementToContainerEnd(container, element) == 0);

//     assert(containerSize(container) == 1);
//     assert(getElementFromContainerAtIndex(container, 0) == element);

//     TElem* poppedElement = popElementFromContainerEnd(container);

//     assert(containerSize(container) == 0);
//     assert(getElementFromContainerAtIndex(container, 0) == NULL);
//     assert(poppedElement == element);

//     TElem* anotherElement = createFile(123, "a state", "good stuff", 6969);

//     assert(pushElementToContainerEnd(container, element) == 0);
//     assert(pushElementToContainerEnd(container, anotherElement) == 0);

//     assert(containerSize(container) == 2);
//     assert(getElementFromContainerAtIndex(container, 0) == element);
//     assert(getElementFromContainerAtIndex(container, 1) == anotherElement);

//     assert(removeElementFromContainerAtIndex(container, 0) == 0);
//     assert(containerSize(container) == 1);
//     assert(getElementFromContainerAtIndex(container, 0) == anotherElement);

//     assert(removeElementFromContainerAtIndex(container, 1) == -2);

//     TElem* someOtherElement = createFile(123, "yikes", "bruv", 12345);

//     assert(insertElementToContainerAtIndex(container, someOtherElement, 0) == 0);
//     assert(containerSize(container) == 2);
//     assert(getElementFromContainerAtIndex(container, 0) == someOtherElement);

//     assert(insertElementToContainerAtIndex(container, someOtherElement, -1) == -3);
//     assert(insertElementToContainerAtIndex(container, someOtherElement, 4) == -3);

//     TElem* yetAnotherElement = createFile(123456, "no", "yes", 12);
    
//     assert(updateElementFromContainerAtIndex(container, yetAnotherElement, 0) == 0);
//     assert(getElementFromContainerAtIndex(container, 0) == yetAnotherElement);

//     assert(updateElementFromContainerAtIndex(container, yetAnotherElement, -1) == -2);

//     destroyFile(anotherElement);
//     destroyFile(yetAnotherElement);
//     destroyContainer(container);
// }

// void testRepository() {
//     printf("Testing the repository...\n");

//     Repository* repository = createRepository();

//     TElem* element = createFile(1, "no", "yes", 12);

//     assert(indexOfElementInRepository(repository, element) == -1);
//     assert(removeElementFromRepository(repository, element) == -5);
//     assert(updateElementFromRepository(repository, element) == -5);
//     assert(containerSize(getContainerFromRepository(repository)) == 0);

//     assert(addElementToRepository(repository, element) == 0);
//     assert(containerSize(getContainerFromRepository(repository)) == 1);
//     assert(getElementFromContainerAtIndex(getContainerFromRepository(repository), 0) == element);
//     assert(getElementFromContainerAtIndex(getContainerFromRepository(repository), 1) == NULL);

//     assert(indexOfElementInRepository(repository, element) == 0);

//     TElem* anotherElement = createFile(1, "a state", "good stuff", 6969);

//     assert(updateElementFromRepository(repository, anotherElement) == 0);
//     assert(removeElementFromRepository(repository, anotherElement) == 0);
//     assert(containerSize(getContainerFromRepository(repository)) == 0);

//     TElem* moreElements = createFile(2, "doofenshmirtz", "good stuff", 69);
//     TElem* evenMoreElements = createFile(3, "agent p", "bad stuff", 420);

//     assert(addElementToRepository(repository, moreElements) == 0);
//     assert(addElementToRepository(repository, moreElements) == -4);

//     assert(addElementToRepository(repository, evenMoreElements) == 0);

//     assert(containerSize(getContainerFromRepository(repository)) == 2);

//     assert(getElementFromRepositoryAtIndex(repository, 0) == moreElements);
//     assert(getElementFromRepositoryAtIndex(repository, 1) == evenMoreElements);

//     assert(removeFromRepositoryElementWithID(repository, 4) == -5);
//     assert(removeFromRepositoryElementWithID(repository, 2) == 0);
//     assert(containerSize(getContainerFromRepository(repository)) == 1);
//     assert(getElementFromRepositoryAtIndex(repository, 0) == evenMoreElements);

//     destroyRepository(repository);
// }

// void testService() {
//     printf("Testing the service...\n");

//     Repository* repository = createRepository();
//     Service* service = createService(repository);

//     assert(deleteFileFromService(service, 2) == -5);
//     assert(updateFileFromService(service, 2, "ceva", "idk", 23) == -5);

//     assert(addFileToService(service, 1, "what", "to do", 42) == 0);
//     assert(addFileToService(service, 1, "don't", "know?", 42) == -4);
//     assert(getElementFromContainerAtIndex(getAllFilesFromService(service), 0)->archiveCatalogueNumber == 1);

//     assert(deleteFileFromService(service, 1) == 0);
//     assert(getElementFromContainerAtIndex(getAllFilesFromService(service), 0) == NULL);

//     assert(addFileToService(service, 1, "what", "to do", 42) == 0);
//     assert(updateFileFromService(service, 1, "don't", "know?", 42) == 0);

//     assert(getElementFromContainerAtIndex(getAllFilesFromService(service), 0)->yearOfCreation == 42);
//     assert(addFileToService(service, 2, "what", "to do", 42) == 0);
//     assert(addFileToService(service, 3, "what", "go to", 42) == 0);
//     assert(addFileToService(service, 4, "what", "to do", 42) == 0);

//     Container* allFiles = getAllFilesFromService(service);
//     assert(containerSize(allFiles) == 4);

//     Container* filteredFiles = getFilesByFileTypeFromService(service, "to do");
//     assert(containerSize(filteredFiles) == 2);

//     for (int i = 0; i < containerSize(filteredFiles); ++i) {
//         assert(strcmp(getElementFromContainerAtIndex(filteredFiles, i)->fileType, "to do") == 0);
//     }

//     destroyContainer(filteredFiles);
//     destroyService(service);
//     destroyRepository(repository);
// }