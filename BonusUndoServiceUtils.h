#pragma once

#include "Service.h"
#include "macros.h"

typedef int (*AddUpdateFunctionCall) (Service*, int, char*, char*, int);
typedef int (*DeleteFunctionCall) (Service*, int);

typedef struct {
    Service* service;
    int archiveCatalogueNumber;
    char stateOfDeterioration[MAX_CHAR_LEN];
    char fileType[MAX_CHAR_LEN];
    int yearOfCreation;
} ParameterList;

ParameterList* ParameterList_create(Service* service, int archiveCatalogueNumber, char* stateOfDeterioration, char* fileType, int yearOfCreation);

void ParameterList_destroy(ParameterList* parameterList);

typedef struct {
    AddUpdateFunctionCall addUpdateFunctionCall;
    DeleteFunctionCall deleteFunctionCall;
    ParameterList* parameterList;
} FunctionCall;

FunctionCall* FunctionCall_create(AddUpdateFunctionCall addUpdateFunctionCall, DeleteFunctionCall deleteFunctionCall, ParameterList* parameterList);

void FunctionCall_destroy(FunctionCall* functionCall);

void FunctionCall_call(FunctionCall* functionCall);

typedef struct {
    FunctionCall* undoFunction;
    FunctionCall* redoFunction;
} Operation;

Operation* Operation_create(FunctionCall* undoFunction, FunctionCall* redoFunction);

void Operation_destroy(void* operation);

void Operation_callUndo(Operation* operation);

void Operation_callRedo(Operation* operation);