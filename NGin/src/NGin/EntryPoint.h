#include "Client.h"

extern ngin::Client* createApplication();

int main()
{
	auto app = createApplication();
	app->run();
	delete app;

	return 0;
}