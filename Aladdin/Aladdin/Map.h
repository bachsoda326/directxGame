#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Camera.h"
#include "Game.h"

class CMap : public CGameObject
{
	CSprite *sprite;
public:
	CMap(int idMap);
	~CMap();

	/*CCamera *camera;
	void SetCamera(CCamera *camera);*/

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

