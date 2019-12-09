#include "SceneManager.h"

SceneManager* SceneManager::__instance = NULL;

SceneManager::SceneManager()
{
}

SceneManager * SceneManager::GetInstance()
{
	if (__instance == NULL) __instance = new SceneManager();
	return __instance;
}

Scene * SceneManager::GetCurrentScene()
{
	return currentScene;
}

void SceneManager::ReplaceScene(Scene * scene)
{
	delete currentScene;

	currentScene = scene;
}


SceneManager::~SceneManager()
{
}
