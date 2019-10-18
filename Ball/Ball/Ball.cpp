#include "Ball.h"
#include "Bar.h"
#include "Number.h"
#include <ctime>
#include "debug.h"

CBall::CBall()
{	
	srand(time(NULL));		
}

void CBall::Update(DWORD dt, CNumber *leftNum, CNumber *rightNum, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();	
	
	CalcPotentialCollisions(coObjects, coEvents);

	// debug
	DebugOut(L"[BEFO] collision: %d\n", coEvents.size());
	
	// No collision occured, proceed normally		
	if (coEvents.size() == 0)
	{
		// debug
		DebugOut(L"[NONE] collision: %d\n", coEvents.size());		

		x += dx;
		y += dy;

		// reset the ball and increase point of the win side (touched the left or right of screen)
		if (x < -20)
		{
			SetPosition(150, 90);
			vx = 0;
			vy = 0;

			if (rightNum->num == 9)
				leftNum->num = 0;

			rightNum->IncreaseNum();
		}
		if (x > 305)
		{
			SetPosition(150, 90);
			vx = 0;
			vy = 0;

			if (leftNum->num == 9)
				rightNum->num = 0;

			leftNum->IncreaseNum();
		}

		// handle the ball move when touched the top or bottom of screen
		if (y <= 1)
		{
			vy = -(vy - 0.02f);
			vx = (vx > 0) ? vx + 0.01 : vx - 0.01;
		}
		if (y >= 180)
		{
			vy = -(vy + 0.02f);
			vx = (vx > 0) ? vx + 0.01 : vx - 0.01;
		}		
	}
	// Collision occured with the bars
	else 
	{
		// debug
		DebugOut(L"[COLL] collision: %d\n", coEvents.size());

		/*float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);*/

		vx = (vx > 0) ? -(vx + 0.01) : -(vx - 0.01);
		vy = (vy > 0) ? vy + 0.01 : vy - 0.01;

		x += dx;
		y += dy;
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

	vx = speed[0];
	vy = speed[0];
}
