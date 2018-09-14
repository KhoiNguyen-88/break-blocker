#include "Header.h"

#undef main

int main() {
	
	Application* app = new Application();
	
	app->Init();

	app->Run(60);

	delete app;


	while (1);
	return 0;

}