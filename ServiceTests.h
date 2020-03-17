#pragma once

void testService();

void Service_addFile__validFile__returnsSuccess();

void Service_addFile__invalidFile__returnsErrorCode();

void Service_updateFile__validFile__returnsSuccess();

void Service_updateFile__invalidFile__returnsErrorCode();

void Service_deleteFile__validFile__returnsSuccess();

void Service_deleteFile__invalidFile__returnsErrorCode();

void Service_getAllFiles__justWorksIGuess();

void Service_getFilesByFileType__returnsCorrectFiles();

void Service_getFilesByYearOfCreation__returnsCorrectFiles();