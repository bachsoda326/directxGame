#pragma once
#include "Scene.h"

class SceneManager
{
private:	
	static SceneManager *__instance;

	Scene *currentScene;

public:
	SceneManager();
	static SceneManager *GetInstance();

	Scene* GetCurrentScene();
	void ReplaceScene(Scene *scene);

	~SceneManager();
};

