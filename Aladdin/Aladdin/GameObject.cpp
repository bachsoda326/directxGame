#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{
	/*x = y = 0;
	vx = vy = 0;
	nx = 1;*/
	isDead = false;
	isActived = false;
	isDie = false;
}

void GameObject::ProcessInput()
{
}

void GameObject::SetObjectFromID()
{
}

void GameObject::LoadResources()
{
}

void GameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;	
	dy = vy*dt;
}

void GameObject::Render()
{
	if (!isDead)
	{
		// // Vector trans giúp dời ảnh theo camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, trans);
	}
}

void GameObject::SetPosition(float x, float y)
{
	float distance_x = this->x - xDraw;
	float distance_y = this->y - yDraw;

	this->x = x;
	this->y = y;
	xDraw = x - distance_x;
	yDraw = y - distance_y;
}

//LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
//{
//	float sl, st, sr, sb;		// static object bbox
//	float ml, mt, mr, mb;		// moving object bbox
//	float t, nx, ny;
//
//	coO->GetBoundingBox(sl, st, sr, sb);
//
//	// deal with moving object: m speed = original m speed - collide object speed
//	float svx, svy;
//	coO->GetSpeed(svx, svy);
//
//	float sdx = svx*dt;
//	float sdy = svy*dt;
//
//	float dx = this->dx - sdx;
//	float dy = this->dy - sdy;
//	// 9:00 20/11
//	GetBoundingBox(ml, mt, mr, mb);
//
//	Game::SweptAABB(
//		ml, mt, mr, mb,
//		dx, dy,
//		sl, st, sr, sb,
//		t, nx, ny
//	);
//
//	ExceptionCase(coO, t, nx, ny);
//
//	if (nx != 0)
//		this->nx = nx;
//	if (ny != 0)
//		this->ny = ny;
//
//	CollisionEvent * e = new CollisionEvent(t, nx, ny, coO);
//	return e;
//}

//void GameObject::ExceptionCase(LPGAMEOBJECT coObj, float &t, float &nx, float &ny)
//{
//	if (this->x > coObj->Left() && this->x < coObj->Right())
//	{
//		if ((int)this->y >= (int)coObj->Top() && (int)this->y <= (int)coObj->Top() + 22 && this->vy > 0)
//		{
//			ny = -1.0f;
//			nx = 0;
//			t = 0.0f;
//			return;
//		}
//	}
//
//	if (this->Top() < coObj->Bottom() - 30 && this->Bottom() > coObj->Top() + 30/* && coObj->collType == CollGround*/)
//	{
//		if (this->Right() >= coObj->Left() && this->Right() < coObj->Right() && this->vx > 0 && this->direction)
//		{
//			nx = -1.0f;
//			ny = 0;
//			t = 0.0f;
//			return;
//		}
//
//		if (this->Left() <= coObj->Right() && this->Left() > coObj->Left() && this->vx < 0 && !this->direction)
//		{
//			nx = 1.0f;
//			ny = 0;
//			t = 0.0f;
//			return;
//		}
//	}
//}

//void GameObject::CalcPotentialCollisions(
//	vector<LPGAMEOBJECT> *coObjects,
//	vector<LPCOLLISIONEVENT> &coEvents)
//{
//	for (UINT i = 0; i < coObjects->size(); i++)
//	{
//		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));
//
//		if (e->t <= 1.0f && e->t >= 0)
//			coEvents.push_back(e);
//		else
//			delete e;
//	}
//
//	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
//}

//void GameObject::FilterCollision(
//	vector<LPCOLLISIONEVENT> &coEvents,
//	vector<LPCOLLISIONEVENT> &coEventsResult,
//	float &min_tx, float &min_ty,
//	float &nx, float &ny)
//{
//	min_tx = 1.0f;
//	min_ty = 1.0f;
//	int min_ix = -1;
//	int min_iy = -1;
//
//	nx = 0.0f;
//	ny = 0.0f;
//
//	coEventsResult.clear();
//
//	for (UINT i = 0; i < coEvents.size(); i++)
//	{
//		LPCOLLISIONEVENT c = coEvents[i];
//
//		if (c->t < min_tx && c->nx != 0) {
//			min_tx = c->t; nx = c->nx; min_ix = i;
//		}
//
//		if (c->t < min_ty  && c->ny != 0) {
//			min_ty = c->t; ny = c->ny; min_iy = i;
//		}
//	}
//
//	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
//	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
//}

float GameObject::Left()
{
	return xDraw;
}

float GameObject::Top()
{
	return yDraw;
}

float GameObject::Right()
{
	return xDraw + w;
}

float GameObject::Bottom()
{
	return yDraw + h;
}

void GameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);

	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	float left = 0;
	float top = 0;
	float width = r - l;
	float height = b - t;

	Sprite *sprite = new Sprite(69, left, top, width, height, 0, 0, bbox);
	D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
	sprite->DrawTest(xDraw, yDraw, trans, 80);
}

void GameObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = xDraw;
	top = yDraw;
	right = xDraw + w;
	bottom = yDraw + h;
}

void GameObject::ChangeFrameSize(GameObject * obj)
{
}

void GameObject::ResetFrameSize(GameObject * obj)
{
}

void GameObject::OnCollision(GameObject * obj, float nx, float ny)
{
}

void GameObject::OnIntersect(GameObject * obj)
{
}

GameObject::~GameObject()
{

}