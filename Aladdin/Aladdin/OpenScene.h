#pragma once
#include "Scene.h"

class OpenScene : public Scene
{
	LPSPRITE openMap;

public:
	OpenScene();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	~OpenScene();
};

