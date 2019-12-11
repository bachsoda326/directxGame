#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Camera.h"
#include "GameObject.h"
#include "Aladdin.h"

class Scene
{
public:
	D3DXFONT_DESC desc;
	LPD3DXFONT numApples, numRubies, numLifes, score, fps;
public:
	Scene();

	virtual void LoadResources();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	void CheckCameraAndWorldMap();
	void LoadFont();
	void DrawFont(LPD3DXFONT font, float x, float y, float width, float height, int value);

	~Scene();
};

