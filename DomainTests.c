#include "DomainTests.h"
#include "Domain.h"

#include <assert.h>
#include <string.h>

void testDomain() {
    File_getArchiveCatalogueNumber__afterCreatingFile__returnsCorrectValue();
    File_getStateOfDeterioration__afterCreatingFile__returnsCorrectValue();
    File_getFileType__afterCreatingFile__returnsCorrectValue();
    File_getYearOfCreation__afterCreatingFile__returnsCorrectValue();
    File_setArchiveCatalogueNumber__afterCreatingFile__setsCorrectValue();
    File_setStateOfDeterioration__afterCreatingFile__setsCorrectValue();
    File_setFileType__afterCreatingFile__setsCorrectValue();
    File_setYearOfCreation__afterCreatingFile__setsCorrectValue();
}

void File_getArchiveCatalogueNumber__afterCreatingFile__returnsCorrectValue() {
    File* file = File_create(123, "bla", "abc", 200);
    assert(File_getArchiveCatalogueNumber(file) == 123);
    File_destroy(file);
}

void File_getStateOfDeterioration__afterCreatingFile__returnsCorrectValue() {
    File* file = File_create(123, "bla", "abc", 200);
    assert(strcmp(File_getStateOfDeterioration(file), "bla") == 0);
    File_destroy(file);
}

void File_getFileType__afterCreatingFile__returnsCorrectValue() {
    File* file = File_create(123, "bla", "abc", 200);
    assert(strcmp(File_getFileType(file), "abc") == 0);
    File_destroy(file);
}

void File_getYearOfCreation__afterCreatingFile__returnsCorrectValue() {
    File* file = File_create(123, "bla", "abc", 200);
    assert(File_getYearOfCreation(file) == 200);
    File_destroy(file);
}

void File_setArchiveCatalogueNumber__afterCreatingFile__setsCorrectValue() {
    File* file = File_create(123, "bla", "abc", 200);
    File_setArchiveCatalogueNumber(file, 5);
    assert(File_getArchiveCatalogueNumber(file) == 5);
    File_destroy(file);
}

void File_setStateOfDeterioration__afterCreatingFile__setsCorrectValue() {
    File* file = File_create(123, "bla", "abc", 200);
    File_setStateOfDeterioration(file, "nope");
    assert(strcmp(File_getStateOfDeterioration(file), "nope") == 0);
    File_destroy(file);
}

void File_setFileType__afterCreatingFile__setsCorrectValue() {
    File* file = File_create(123, "bla", "abc", 200);
    File_setFileType(file, "big brain");
    assert(strcmp(File_getFileType(file), "big brain") == 0);
    File_destroy(file);
}

void File_setYearOfCreation__afterCreatingFile__setsCorrectValue() {
    File* file = File_create(123, "bla", "abc", 200);
    File_setYearOfCreation(file, 2);
    assert(File_getYearOfCreation(file) == 2);
    File_destroy(file);
}