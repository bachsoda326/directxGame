#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"

class BlueHeart : public Item
{
public:
	BlueHeart(float left, float top, float width, float height);

	LPANIMATION animationDefault;

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	// action of GenieFace
	void Active();
	void NonActive();

	~BlueHeart();
};

