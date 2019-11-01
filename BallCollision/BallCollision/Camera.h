#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class CCamera
{
public:
	CCamera(int width, int height);

	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 pos);

	int GetWidth();
	int GetHeight();

	D3DXVECTOR3 GetPosition();
	RECT GetBound();

	~CCamera();

private:
	int mWidth, mHeight;

	D3DXVECTOR3 mPosition;
};

