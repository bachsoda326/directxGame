#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Camera.h"
#include "GameObject.h"
#include "Aladdin.h"

class Scene
{
public:
	Scene();

	virtual void LoadResources();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	void CheckCameraAndWorldMap();

	~Scene();
};

