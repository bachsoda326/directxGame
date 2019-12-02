#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"

class Peddler : public Item
{
public:
	Peddler(float left, float top, float width, float height);

	LPANIMATION animationStand,
		animationCreate;

	enum PeddlerStates
	{
		STANDING,
		CREATING
	};

	enum PeddlerAnimations
	{
		ANI_STAND,
		ANI_CREATE
	};

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	void SetAnimation(PeddlerAnimations ani);

	~Peddler();
};

