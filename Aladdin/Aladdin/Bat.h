#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class Bat : public GameObject
{
public:
	Bat(float left, float top, float width, float height);

	LPANIMATION animationStand,		
		animationAttack,
		animationDieByApple,
		animationDie;

	enum BatStates
	{
		STANDING,
		ATTACKING,
		DIEBYAPPLE,
		DIE
	};

	enum BatAnimations
	{
		ANI_STAND,
		ANI_ATTACK,
		ANI_DIE_BY_APPLE,
		ANI_DIE
	};

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	void SetAnimation(BatAnimations ani);

	~Bat();
};

