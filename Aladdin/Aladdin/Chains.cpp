#include "Chains.h"

Chains::Chains(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	w = width;
	h = height;
	x = xDraw;
	y = yDraw;
	direction = true;
	collType = CollChains;
}

void Chains::Render()
{
	//RenderBoundingBox();
}

Chains::~Chains()
{
}
