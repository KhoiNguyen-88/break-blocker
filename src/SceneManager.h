#pragma once

class SceneManager
{
	static SceneManager* instance;

	SceneManager();

	Scene*	m_activeScene;
	Scene*	m_nextScene;

public:
	static SceneManager* GetInstance();
	static void FreeInstance();

	// Object method
	void Update(Uint32 dt);
	void Render();

	void HandleKeyEvent(char key, bool state);
	void HandleMouseEvent(int x, int y, int button);

	void ChangeScene(Scene* nextScene);
};

#define SCENE_MGR SceneManager::GetInstance()
