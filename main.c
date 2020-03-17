#include "Repository.h"
#include "UndoService.h"
#include "BonusUndoService.h"
#include "Service.h"
#include "UI.h"
#include "macros.h"

#include "Tests.h"

#define RUN_TESTS

int main() {

#ifdef RUN_TESTS
	#ifndef BONUS_UNDO_SERVICE
		runAllTests();
		return 0;
	#endif
#endif

	Repository* repository = Repository_create();

#ifndef BONUS_UNDO_SERVICE
	UndoService* undoService = UndoService_create();
#else
	BonusUndoService* undoService = BonusUndoService_create();
#endif

	Service* service = Service_create(repository, undoService);
	UI* ui = UI_create(service);

	UI_run(ui);

	Repository_destroy(repository);

#ifndef BONUS_UNDO_SERVICE
	UndoService_destroy(undoService);
#else
	BonusUndoService_destroy(undoService);
#endif

	Service_destroy(service);
	UI_destroy(ui);
    return 0;
}