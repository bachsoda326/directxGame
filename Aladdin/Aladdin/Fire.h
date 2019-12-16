#pragma once
#include "Enemy.h"
#include "FireCarpet.h"
#include "Boss.h"

class FireCarpet;
class Boss;

class Fire : public Enemy
{
private:	
	FireCarpet *fireCarpet;
	Boss *boss;

public:
	int typeFire;

	Fire();

	LPANIMATION animationBurn,
		animationFire;

	enum FireStates
	{
		MOVING,
		DESTROY
	};

	enum FireAnimations
	{		
		ANI_BURN,
		ANI_FIRE
	};

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void SetAnimation(FireAnimations ani);
	//get Fire Carpet
	void GetFireCarpet(FireCarpet *obj);
	//get Boss
	void GetBoss(Boss*obj);

	//action of Fire
	void Move();
	void Destroy();

	void OnCollision(GameObject *obj, float nx, float ny);
	void OnIntersect(GameObject *obj);

	~Fire();
};

