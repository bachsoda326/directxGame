#pragma once
#include "Scene.h"
#include "Grid.h"
#include "TileMap.h"
#include "Abu.h"

class NextScene : public Scene
{
	LPSPRITE nextMap;
	Aladdin *aladdin = Aladdin::GetInstance();
	Abu *abu = Abu::GetInstance();
	int sceneId;

public:
	// 3: m�n Boss || 4: m�n End
	NextScene(int sceneId);
		
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	~NextScene();
};

