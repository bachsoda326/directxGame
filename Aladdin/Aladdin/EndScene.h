#pragma once
#include "Scene.h"
#include "Grid.h"
#include "TileMap.h"

class EndScene : public Scene
{
	LPSPRITE endMap;
	Aladdin *aladdin = Aladdin::GetInstance();

public:
	EndScene();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	~EndScene();
};

