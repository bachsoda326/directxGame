#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Camera.h"

//#define BALL_BBOX_WIDTH  16
//#define BALL_BBOX_HEIGHT 16
//#define BALL_SPEED 0.1f

class CBall : public CGameObject
{
private:
	float speed[2] = { -BALL_SPEED, BALL_SPEED };
public:
	CBall();

	CCamera *camera;
	void SetCamera(CCamera *camera);
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetRanDomPosition();
	void CheckCollision(vector<LPGAMEOBJECT> *coObjects);
	//void SetSpeed();
};

