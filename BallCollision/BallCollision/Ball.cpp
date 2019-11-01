#include "Ball.h"
#include <ctime>
#include "debug.h"

CBall::CBall()
{	
	
}

void CBall::SetCamera(CCamera * camera)
{
	this->camera = camera;
}

void CBall::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);	
}

void CBall::Render()
{
	if (camera)
	{
		// Vector trans to support move camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - camera->GetPosition().x), floor(SCREEN_HEIGHT / 2 - camera->GetPosition().y));
		animations[0]->Render(x, y, trans);
	}
	else
		animations[0]->Render(x, y, D3DXVECTOR2(0,0));
	//RenderBoundingBox();
}

void CBall::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BALL_BBOX_WIDTH;
	b = y + BALL_BBOX_HEIGHT;
}

void CBall::SetRanDomPosition()
{
	int xBall = 30 + rand() % RANDOM_WIDTH - 29;
	int yBall = 30 + rand() % RANDOM_HEIGHT - 29;
	SetPosition(xBall, yBall);
}

void CBall::CheckCollision(vector<LPGAMEOBJECT> *coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();	
	DebugOut(L"[KT] coObjs: %d\n", coObjects->size());

	CalcPotentialCollisions(coObjects, coEvents);

	DebugOut(L"[BEFO] collision: %d\n", coEvents.size());
	
	// No collision occured, proceed normally		
	if (coEvents.size() == 0)
	{
		// debug
		DebugOut(L"[NONE] collision: %d\n", coEvents.size());	

		if (this->x < 0)
		{
			vx = 0;
			this->x = 0;
		}
		else if (this->y < 0)
		{
			vy = 0;
			this->y = 0;
		}
		else if (this->x > MAP_WIDTH - BALL_BBOX_WIDTH)
		{
			vx = 0;
			this->x = MAP_WIDTH - BALL_BBOX_WIDTH;
		}
		else if (this->y > MAP_HEIGHT - BALL_BBOX_HEIGHT)
		{
			vy = 0;
			this->y = MAP_HEIGHT - BALL_BBOX_HEIGHT;
		}
		else
		{
			x += dx;
			y += dy;
		}		
	}
	// Collision occured with the bars
	else 
	{
		// debug
		DebugOut(L"[COLL] collision: %d\n", coEvents.size());

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// Collision logic with s.t
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBall *>(e->obj)) // if e->obj is s.t 
			{
				CBall *otherBall = dynamic_cast<CBall *>(e->obj);
								
				//if (e->nx < 0)			// touch leftside of otherBall
				//{
				//	vx = -(vx + 0.1);	
				//}
				//else if (e->nx > 0)		// touch rightside of otherBall
				//{
				//	vx = -(vx - 0.1);
				//}
				//else if (e->ny < 0)		// touch topside of otherBall
				//{
				//	vy = -(vy + 0.1);
				//}
				//else if (e->ny > 0)		// touch botside of otherBall
				//{
				//	vy = -(vy - 0.1);
				//}

				if (e->nx != 0)				// touch left,rightside of otherBall
					vx = -vx;
				else if (e->ny != 0)		// touch top,botside of otherBall
				{
					vy = -vy;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

//void CBall::SetSpeed()
//{
//	int randomx = rand() % 2;
//	int randomy = rand() % 2;
//
//	vx = speed[randomx];
//	vy = speed[randomy];
//}
