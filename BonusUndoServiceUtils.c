#include "BonusUndoServiceUtils.h"

#include <stdlib.h>
#include <string.h>

FunctionCall* FunctionCall_create(AddUpdateFunctionCall addUpdateFunctionCall, DeleteFunctionCall deleteFunctionCall, ParameterList* parameterList) {
    FunctionCall* functionCall = (FunctionCall*) malloc(sizeof(FunctionCall));
    functionCall->addUpdateFunctionCall = addUpdateFunctionCall;
    functionCall->deleteFunctionCall = deleteFunctionCall;
    functionCall->parameterList = parameterList;
    return functionCall;
}

void FunctionCall_destroy(FunctionCall* functionCall) {
    ParameterList_destroy(functionCall->parameterList);
    free(functionCall);
}

void FunctionCall_call(FunctionCall* functionCall) {
    if (functionCall->addUpdateFunctionCall == NULL) {
        functionCall->deleteFunctionCall(
            functionCall->parameterList->service, 
            functionCall->parameterList->archiveCatalogueNumber
        );
    } else {
        functionCall->addUpdateFunctionCall(
            functionCall->parameterList->service, 
            functionCall->parameterList->archiveCatalogueNumber, 
            functionCall->parameterList->stateOfDeterioration, 
            functionCall->parameterList->fileType, 
            functionCall->parameterList->yearOfCreation
        );
    }
}

ParameterList* ParameterList_create(Service* service, int archiveCatalogueNumber, char* stateOfDeterioration, char* fileType, int yearOfCreation) {
    ParameterList* parameterList = (ParameterList*) malloc(sizeof(ParameterList));
    parameterList->service = service;
    parameterList->archiveCatalogueNumber = archiveCatalogueNumber;
    strcpy(parameterList->stateOfDeterioration, stateOfDeterioration);
    strcpy(parameterList->fileType, fileType);
    parameterList->yearOfCreation = yearOfCreation;
    return parameterList;
}

void ParameterList_destroy(ParameterList* parameterList) {
    free(parameterList);
}

Operation* Operation_create(FunctionCall* undoFunction, FunctionCall* redoFunction) {
    Operation* operation = (Operation*) malloc(sizeof(Operation));
    operation->undoFunction = undoFunction;
    operation->redoFunction = redoFunction;
    return operation;
}

void Operation_destroy(void* operation) {
    FunctionCall_destroy(((Operation*) operation)->undoFunction);
    FunctionCall_destroy(((Operation*) operation)->redoFunction);
    free(operation);
}

void Operation_callUndo(Operation* operation) {
    FunctionCall_call(operation->undoFunction);
}

void Operation_callRedo(Operation* operation) {
    FunctionCall_call(operation->redoFunction);
}