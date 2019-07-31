#include "MainLevel.h"

extern ngin::MainLevel* setMainLevel();

int main()
{
	auto app = setMainLevel();
	app->run();
	delete app;

	return 0;
}