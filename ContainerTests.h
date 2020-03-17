#pragma once

void testContainer();

void Container_expandIfCapacityReached__whenCapacityIsZero__expandsCapacityToOne();

void Container_expandIfCapacityReached__whenCapacityNotZero__doublesCapacity();

void Container_pushElementToEnd__validInput__appendsElement();

void Container_getElementAtIndex__validIndex__returnsElement();

void Container_getElementAtIndex__invalidIndex__returnsNULL();

void Container_deleteElementAtIndex__validIndex__returnsSuccess();

void Container_deleteElementAtIndex__invalidIndex__returnsErrorCode();

void Container_updateElementAtIndex__validIndex__returnsSuccess();

void Container_updateElementAtIndex__invalidIndex__returnsErrorCode();

void Container_size__afterAddingTwoElements__returnsCorrectSize();

void Container_swapElementsAtIndices__validIndices__returnsSuccess();

void Container_swapElementsAtIndices__invalidIndices__returnsErrorCode();

void Container_popElementFromEnd__whenContainerIsNotEmpty__returnsLastElementAndRemovesFromEnd();

void Container_popElementFromEnd__whenContainerIsEmpty__returnsNULL();