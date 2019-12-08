#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class BoomSkeleton : public GameObject
{
public:
	BoomSkeleton(float left, float top, float width, float height);

	LPANIMATION animationDefault;
		
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	
	~BoomSkeleton();
};

