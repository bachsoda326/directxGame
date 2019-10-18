#pragma once
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"

class CNumber
{
public:
	float x;
	float y;	

	int num = 0;

	vector<LPANIMATION> animations;

	CNumber();
	~CNumber();

	void SetPosition(float x, float y) { this->x = x, this->y = y; }

	void Render();
	void AddAnimation(int aniId);
	void IncreaseNum();
};

