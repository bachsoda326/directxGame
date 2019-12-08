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

	// action of GenieJar
	void Active();
	void NonActive();

	~GenieJar();
};

