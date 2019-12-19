#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Item.h"

class AladdinFace : public Item
{
public:
	LPANIMATION animationDefault;	// animation mặc định

public:
	AladdinFace();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	~AladdinFace();
};

