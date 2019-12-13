#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Enemy.h"

class Bat : public Enemy
{
public:
	Bat(float left, float top, float width, float height);

	LPANIMATION animationStand,
		animationAttack,
		animationDieByApple;

	enum BatStates
	{
		STANDING,
		PREPARING,
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

	void SetAnimation(BatAnimations ani);

	// Action
	void Stand();
	void Attack();
	void Die();

	// Change and reset frame size
	void ChangeFrameSize(GameObject*obj);
	void ResetFrameSize(GameObject*obj);

	void OnIntersect(GameObject *obj);

	~Bat();
};

