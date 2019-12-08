#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"

class Ruby : public Item
{
public:
	Ruby(float left, float top, float width, float height);

	LPANIMATION animationDefault;

	void LoadResources();

	// action of GenieFace
	void Active();
	void NonActive();

	~Ruby();
};

