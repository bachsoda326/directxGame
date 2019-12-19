#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"

class Ruby : public Item
{
public:
	LPANIMATION animationDefault;		// animation mặc định

public:
	// Xài cho Ruby của Aladdin
	Ruby();
	Ruby(float left, float top, float width, float height);	

	void LoadResources();
	void Render();

	// Action của ruby
	void Active();						// đc ăn
	void NonActive();					// chưa đc ăn

	~Ruby();
};

