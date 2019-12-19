#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"

class BlueHeart : public Item
{
public:
	LPANIMATION animationDefault;		// animation mặc định

public:
	BlueHeart(float left, float top, float width, float height);	

	void LoadResources();

	// Action của tim xanh
	void Active();						// đc ăn
	void NonActive();					// chưa đc ăn

	~BlueHeart();
};

