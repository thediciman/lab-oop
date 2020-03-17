#include "Tests.h"
#include "DomainTests.h"
#include "ContainerTests.h"
#include "RepositoryTests.h"
#include "UndoServiceTests.h"
#include "ServiceTests.h"

void runAllTests() {
    testDomain();
    testContainer();
    testRepository();
    testUndoService();
    testService();
}