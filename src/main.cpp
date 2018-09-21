#include "Header.h"

#undef main

int main() {
	
	Application* app = new Application();

	app->Init();
	app->SetStartScene(new MainMenu());

	app->Run(60);

	delete app;

	return 0;

}