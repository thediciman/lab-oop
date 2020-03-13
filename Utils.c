#include "Utils.h"

#include "Domain.h"

Container* Utils_getDeepCopyOfFileContainer(Container* container) {
    Container* deepCopy = Container_create(Container_getDestroyElementFunction(container));
    for (int i = 0; i < Container_size(container); ++i) {
        File* currentFile = Container_getElementAtIndex(container, i);
        File* currentFileCopy = File_create(
            File_getArchiveCatalogueNumber(currentFile),
            File_getStateOfDeterioration(currentFile),
            File_getFileType(currentFile),
            File_getYearOfCreation(currentFile)
        );
        Container_pushElementToEnd(deepCopy, currentFileCopy);
    }
    return deepCopy;
}