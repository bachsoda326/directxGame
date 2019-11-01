#include "Camera.h"


CCamera::CCamera(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mPosition = D3DXVECTOR3(0, 0, 0);
}


CCamera::~CCamera()
{

}

void CCamera::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void CCamera::SetPosition(D3DXVECTOR3 pos)
{
	mPosition = pos;
}

D3DXVECTOR3 CCamera::GetPosition()
{
	return mPosition;
}

RECT CCamera::GetBound()
{
	RECT bound;

	bound.left = mPosition.x - mWidth / 2;
	bound.right = bound.left + mWidth;;
	bound.top = mPosition.y - mHeight / 2;
	bound.bottom = bound.top + mHeight;

	return bound;
}

int CCamera::GetWidth()
{
	return mWidth;
}

int CCamera::GetHeight()
{
	return mHeight;
}