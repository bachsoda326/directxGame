#include "Bar.h"

void CBar::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;

	if (y <= 1 || y >= 150)
		SetState(BAR_STATE_STAND);
}

void CBar::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CBar::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BAR_BBOX_WIDTH;
	b = y + BAR_BBOX_HEIGHT;
}

void CBar::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAR_STATE_UP:
		vy = -BAR_SPEED;
		break;
	case BAR_STATE_DOWN:
		vy = BAR_SPEED;
		break;
	case BAR_STATE_STAND:
		vy = 0;
		break;
	}
}