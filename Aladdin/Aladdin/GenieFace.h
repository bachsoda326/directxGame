#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"

class GenieFace : public Item
{
public:
	GenieFace(float left, float top, float width, float height);

	LPANIMATION animationDefault,
		animationExplosion_Actived;	

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);	

	// action of GenieFace
	void Active();
	void NonActive();

	~GenieFace();
};

