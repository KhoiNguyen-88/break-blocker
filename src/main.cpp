#include "Header.h"

#undef main

int main() {

	Application* app = new Application();
	
	app->Init();

	app->Run();

	delete app;
	return 0;
}