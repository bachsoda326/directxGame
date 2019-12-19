#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class Bone : public GameObject
{
public:
	LPANIMATION animationDefault;		// animation mặc định

public:
	Bone();	

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	~Bone();
};

