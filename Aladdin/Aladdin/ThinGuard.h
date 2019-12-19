#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Enemy.h"

class ThinGuard : public Enemy
{
private:
	// số lượng máu của thin guard
	int blood;
public:
	enum ThinGuardStates
	{
		STANDING,					// đứng		
		CUTTING_1,					// chém
		HURT,						// bị đánh
		DIE,						// chết
		RUNNING						// chạy
	};
	enum ThinGuardAnimations
	{		
		ANI_CUT_1,
		ANI_HURT,
		ANI_DIE,
		ANI_RUN
	};
	LPANIMATION animationCut_1,		// animation chém		
		animationHurt,				// animation bị đánh
		animationDie,				// animation chết
		animationRun;				// animation chạy

public:
	ThinGuard(float left, float top, float width, float height);

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
		
	// Action của enemy gầy
	void Cut();						// chém	
	void Stand();					// đứng
	void Hurt();					// bị đánh
	void Die();						// chết
	void Run();						// chạy

	void SetAnimation(ThinGuardAnimations ani);

	// Đổi và reset frame size (khoảng cách để xét va chạm với các obj khác)
	void ChangeFrameSize(GameObject*obj);
	void ResetFrameSize(GameObject*obj);

	// Giao nhau vs Aladdin, táo
	void OnIntersect(GameObject *obj);

	~ThinGuard();
};

