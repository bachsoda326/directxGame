#include "Camera.h"
#include "Constants.h"

Camera* Camera::__instance = NULL;

Camera::Camera()
{
	mPosition = D3DXVECTOR3(0, 0, 0);

	mWidth = SCREEN_WIDTH;
	mHeight = SCREEN_HEIGHT;
}

Camera * Camera::GetInstance()
{
	if (__instance == NULL) __instance = new Camera();
	return __instance;
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
	mPosition = pos;
}

void Camera::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

D3DXVECTOR3 Camera::GetPosition()
{
	return mPosition;
}

int Camera::GetWidth()
{
	return mWidth;
}

int Camera::GetHeight()
{
	return mHeight;
}

RECT Camera::GetBound()
{
	RECT bound;

	bound.left = mPosition.x - mWidth / 2;
	bound.right = bound.left + mWidth;
	bound.top = mPosition.y - mHeight / 2;
	bound.bottom = bound.top + mHeight;

	return bound;
}

Camera::~Camera()
{

}