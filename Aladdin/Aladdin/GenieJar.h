#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"

class GenieJar : public Item
{
public:
	LPANIMATION animationDefault;		// animation mặc định

public:
	GenieJar(float left, float top, float width, float height);

	void LoadResources();

	// Action của bình Genie (điểm hồi sinh)
	void Active();						// đc ăn
	void NonActive();					// chưa đc ăn

	~GenieJar();
};

