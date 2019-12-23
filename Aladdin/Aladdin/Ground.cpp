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
}

void Ground::Render()
{
	//RenderBoundingBox();
}

Ground::~Ground()
{
}
