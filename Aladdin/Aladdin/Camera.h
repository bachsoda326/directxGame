#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
public:	
	Camera();
	static Camera * GetInstance();

	void SetPosition(D3DXVECTOR3 pos);
	void SetPosition(float x, float y);	

	D3DXVECTOR3 GetPosition();
	int GetWidth();
	int GetHeight();	
	// Trả về biên của camera thông qua RECT
	RECT GetBound();

	~Camera();

private:
	static Camera * __instance;

	int mWidth, mHeight;

	D3DXVECTOR3 mPosition;
};

