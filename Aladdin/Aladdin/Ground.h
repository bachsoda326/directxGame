#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class Ground : public GameObject
{
public:
	Ground(float left, float top, float width, float height);		

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	//void SetAnimation(NormalGuardAnimations ani);

	~Ground();
};

