#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Enemy.h"

class NormalGuard : public Enemy
{
private:
	// số lượng máu của normal guard
	int blood;	

public:
	NormalGuard();
	NormalGuard(float left, float top, float width, float height);

	LPANIMATION animationIdle,
		animationRun,
		animationRunOnFire,
		animationCut_1,
		animationCut_2,
		animationHurt;

	enum NormalGuardStates
	{
		RUNNING,
		RUNNING_ON_FIRE,
		STANDING,
		CUTTING_1,
		CUTTING_2,
		HURT,
		PROVOKE,		
		DIE
	};

	enum NormalGuardAnimations
	{
		ANI_IDLE,
		ANI_RUN,
		ANI_RUN_ON_FIRE,
		ANI_CUT_1,
		ANI_CUT_2,
		ANI_HURT
	};

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	
	void SetAnimation(NormalGuardAnimations ani);
	
	// Action
	void Cut();
	void Run();
	void Stand();
	void Hurt();	
	void Provoke();
	void Die();

	// Change and reset frame size
	void ChangeFrameSize(GameObject*obj);
	void ResetFrameSize(GameObject*obj);

	void OnIntersect(GameObject *obj);
	
	~NormalGuard();
};

