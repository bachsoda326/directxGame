#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Item.h"

class AladdinFace : public Item
{
public:
	AladdinFace();

	LPANIMATION animationDefault;

	//init object
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	//process input
	virtual void ProcessInput();

	~AladdinFace();
};

