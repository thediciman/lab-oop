#pragma once

void testRepository();

void Repository_indexOfElement__invalidElement__returnsErrorCode();

void Repository_indexOfElement__validElement__returnsCorrectIndex();

void Repository_addElement__validElement__returnsSuccess();

void Repository_addElement__duplicateElement__returnsErrorCode();

void Repository_deleteElement__validElement__returnsSuccess();

void Repository_deleteElement__invalidElement__returnsErrorCode();

void Repository_deleteElementWithID__validID__returnsSuccess();

void Repository_deleteElementWithID__invalidID__returnsErrorCode();

void Repository_updateElement__validElement__returnsSuccess();

void Repository_updateElement__invalidElement__returnsErrorCode();

void Repository_getContainer__returnsContainerDUHHHH();

void Repository_replaceContainer__replacesContainer();

void Repository_getFileByID__validID__returnsFile();

void Repository_getFileByID__invalidID__returnsNULL();