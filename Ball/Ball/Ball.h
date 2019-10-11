#pragma once
#include "GameObject.h"

#define BALL_BBOX_WIDTH  16
#define BALL_BBOX_HEIGHT 16

class CBall : public CGameObject
{
	float speed[2] = { -0.1f, 0.1f };
public:
	CBall();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetSpeed();
};

