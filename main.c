#include "Repository.h"
#include "UndoService.h"
#include "Service.h"
#include "UI.h"

int main() {
	Repository* repository = Repository_create();
	UndoService* undoService = UndoService_create();
	Service* service = Service_create(repository, undoService);
	UI* ui = UI_create(service);

	UI_run(ui);

	Repository_destroy(repository);
	UndoService_destroy(undoService);
	Service_destroy(service);
	UI_destroy(ui);

    return 0;
}