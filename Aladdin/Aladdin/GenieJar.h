#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"

class GenieJar : public Item
{
public:
	GenieJar(float left, float top, float width, float height);

	LPANIMATION animationDefault;

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	// action of GenieJar
	void Active();
	void NonActive();

	~GenieJar();
};

