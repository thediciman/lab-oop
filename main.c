#include "Repository.h"
#include "Service.h"
#include "UI.h"

int main() {
	Repository* repository = Repository_create();
	Service* service = Service_create(repository);
	UI* ui = UI_create(service);
	UI_run(ui);
	Repository_destroy(repository);
	Service_destroy(service);
	UI_destroy(ui);
    return 0;
}