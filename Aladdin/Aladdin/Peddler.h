#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"
#include "Stall.h"

class Peddler : public Item
{
private:
	Stall *stall;
	bool canCreate;

public:
	Peddler(float left, float top, float width, float height);

	LPANIMATION animationStand,
		animationCreate;

	enum PeddlerStates
	{
		STANDING,
		CREATING,
		DONE
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

	void Stand();
	void Create();
	void CreateStall();

	void OnIntersect(GameObject *obj);

	~Peddler();
};

