#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class CCamera
{
public:	
	CCamera();

	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 pos);

	int GetWidth();
	int GetHeight();

	D3DXVECTOR3 GetPosition();
	RECT GetBound();

	static CCamera * GetInstance();

	~CCamera();

private:
	static CCamera * __instance;
	int mWidth, mHeight;

	D3DXVECTOR3 mPosition;
};

