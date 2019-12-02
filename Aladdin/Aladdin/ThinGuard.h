#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class ThinGuard : public GameObject
{
public:
	ThinGuard(float left, float top, float width, float height);

	LPANIMATION animationRun,
		animationCut_1,
		animationHurt,
		animationDie;

	enum ThinGuardStates
	{
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
	void Render();

	void SetAnimation(ThinGuardAnimations ani);

	~ThinGuard();
};

