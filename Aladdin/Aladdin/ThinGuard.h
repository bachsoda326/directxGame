#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class ThinGuard : public GameObject
{
private:
	// số lượng máu của thin guard
	int blood;

public:
	ThinGuard(float left, float top, float width, float height);

	LPANIMATION animationRun,
		animationCut_1,
		animationHurt,
		animationDie;

	enum ThinGuardStates
	{
		STANDING,
		RUNNING,
		CUTTING_1,
		HURT,
		PROVOKE,
		DIE
	};

	enum ThinGuardAnimations
	{
		ANI_RUN,		
		ANI_CUT_1,
		ANI_HURT,
		ANI_DIE
	};

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void SetAnimation(ThinGuardAnimations ani);

	//action
	void Cut();
	void Run();
	void Stand();
	void Hurt();
	void Die();

	//change and reset frame size
	void ChangeFrameSize(GameObject*obj);
	void ResetFrameSize(GameObject*obj);

	void OnIntersect(GameObject *obj);

	~ThinGuard();
};

