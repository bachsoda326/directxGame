#include "Map.h"



CMap::CMap(int idMap)
{
	sprite = CSprites::GetInstance()->Get(idMap);
}

CMap::~CMap()
{
}

//void CMap::SetCamera(CCamera * camera)
//{
//	this->camera = camera;
//}

void CMap::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
}

void CMap::Render()
{	
	if (true)
	{
		// Vector trans to support move camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - CCamera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - CCamera::GetInstance()->GetPosition().y));
		sprite->Draw(x, y, trans);
	}
	else
		sprite->Draw(x, y, D3DXVECTOR2(0, 0));
}

void CMap::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BALL_BBOX_WIDTH;
	b = y + BALL_BBOX_HEIGHT;
}