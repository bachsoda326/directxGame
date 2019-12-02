#include "Ground.h"
#include "Textures.h"

Ground::Ground(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	w = width;
	h = height;
	x = xDraw;
	y = yDraw;
}

void Ground::LoadResources()
{	
}

void Ground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
}

void Ground::Render()
{
	//if (true)
	//{
	//	// // Vector trans giúp dời ảnh theo camera
	//	D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
	//	currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, trans);
	//}
	//else
	//	currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0));

	//RenderBoundingBox();
}

Ground::~Ground()
{
}
