#pragma once
#include "Boss.h"
#include "Aladdin.h"

class Boss;

class Star: public GameObject
{
	Boss *boss;

public:
	Star();

	LPANIMATION animationFling,
		animationDestroy;

	enum StarStates
	{
		FLING,
		DESTROY
	};

	enum StarAnimations
	{
		ANI_FLING,
		ANI_DESTROY
	};

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);	

	void SetAnimation(StarAnimations ani);
	void GetBoss(Boss *obj);

	void Destroy();
	void Fly();

	void OnCollision(GameObject *obj, float nx, float ny);
	void OnIntersect(GameObject *obj);

	~Star();
};

