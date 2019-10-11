#include "Ball.h"
#include "Bar.h"
#include "Number.h"
#include <ctime>

CBall::CBall()
{	
	srand(time(NULL));		
}

void CBall::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// update ball vx, vy, position to center screen when the ball touch left||right edge screen
	if (x < -20 || x > 305)
	{
		SetPosition(150, 80);
		vx = 0;
		vy = 0;
	}
	
	CalcPotentialCollisions(coObjects, coEvents);
	
	// No collision occured, proceed normally		
	if (y <= 1)		// ball touch the top edge
	{
		vy = -(vy - 0.02f);
		vx = (vx > 0) ? vx + 0.01 : vx - 0.01;
	}
	if (y >= 187)	// ball touch the bottom edge
	{
		vy = -(vy + 0.02f);
		vx = (vx > 0) ? vx + 0.01 : vx - 0.01;
	}

	// collision occured: touch left||right bar
	if (coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		vx = (vx > 0) ? -(vx + 0.01) : -(vx - 0.01);
		vy = (vy > 0) ? vy + 0.01 : vy - 0.01;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBall::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CBall::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BALL_BBOX_WIDTH;
	b = y + BALL_BBOX_HEIGHT;
}

void CBall::SetSpeed()
{
	int randomx = rand() % 2;
	int randomy = rand() % 2;

	vx = speed[randomx];
	vy = speed[randomy];
}
