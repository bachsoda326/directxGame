#pragma once
#include "GameObject.h"

#define BAR_BBOX_WIDTH  10
#define BAR_BBOX_HEIGHT 50

#define BAR_STATE_STAND 0
#define BAR_STATE_UP 100
#define BAR_STATE_DOWN 200

#define BAR_SPEED 0.15f

class CBar : public CGameObject
{
public:
	void SetState(int state);
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

