#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{	
	isDead = false;
	isActived = false;
	isDie = false;
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
		// Vector trans giúp dời ảnh theo camera
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

vector<GameObject*>* GameObject::GetList()
{
	return NULL;
}

void GameObject::ResetProper()
{
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