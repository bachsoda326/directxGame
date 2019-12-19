#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"

class GenieFace : public Item
{
public:
	LPANIMATION animationDefault,			// animation mặc định
		animationExplosion_Actived;			// animation khi đc ăn

public:
	GenieFace(float left, float top, float width, float height);

	void LoadResources();

	// Action của item mặt Genie
	void Active();							// đc ăn
	void NonActive();						// chưa đc ăn

	~GenieFace();
};

