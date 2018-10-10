#include "Header.h"

#undef main

int main() {
	
	Application* app = new Application();

	app->Init();
	SCENE_MGR->ChangeScene(new MainMenu());

	app->Run(60);

	delete app;

	return 0;

}