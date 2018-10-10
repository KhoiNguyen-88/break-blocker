#include "Header.h"

SceneManager*  SceneManager::instance = NULL;

SceneManager::SceneManager() : m_activeScene(NULL), m_nextScene(NULL)
{

}

SceneManager* SceneManager::GetInstance()
{
	if (instance == NULL)
	{
		instance = new SceneManager();
	}

	return instance;
}

void SceneManager::FreeInstance()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

void SceneManager::Update(Uint32 dt)
{
	if (m_nextScene)
	{
		if (m_activeScene)
		{
			m_activeScene->Destroy();
			delete m_activeScene;
		}

		m_activeScene = m_nextScene;
		m_activeScene->Init();

		m_nextScene = NULL;
	}

	if (m_activeScene)
		m_activeScene->Update(dt);
}

void SceneManager::Render()
{
	if (m_activeScene)
		m_activeScene->Render();
}

void SceneManager::HandleKeyEvent(char key, bool state)
{
	if (m_activeScene)
		m_activeScene->HandleKeyEvent(key, state);
}

void SceneManager::HandleMouseEvent(int x, int y, int button)
{
	if (m_activeScene)
		m_activeScene->HandleMouseEvent(x, y, button);
}

void SceneManager::ChangeScene(Scene * nextScene)
{
	m_nextScene = nextScene;
}
