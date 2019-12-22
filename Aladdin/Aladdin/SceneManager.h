#pragma once
#include "Scene.h"
#include "OpenScene.h"
#include "DungeonScene.h"
#include "BossScene.h"
#include "NextScene.h"
#include "EndScene.h"

class SceneManager
{
private:	
	static SceneManager *__instance;
	// màn hiện tại
	Scene *currentScene;

public:
	SceneManager();
	static SceneManager *GetInstance();

	// lấy màn hiện tại
	Scene* GetCurrentScene();
	// thay đổi màn
	void ReplaceScene(Scene *scene);

	~SceneManager();
};

