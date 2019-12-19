#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Enemy.h"

class NormalGuard : public Enemy
{
private:
	// số lượng máu của enemy béo
	int blood;	
public:
	enum NormalGuardStates
	{		
		STANDING,						// đứng
		CUTTING_1,						// chém 1
		CUTTING_2,						// chém 2
		HURT,							// bị đánh
		PROVOKE,						// khiêu khích
		DIE,							// chết
		RUNNING,						// chạy
		RUNNING_ON_FIRE
	};
	enum NormalGuardAnimations
	{
		ANI_IDLE,						// đứng và khiêu khích	
		ANI_CUT_1,
		ANI_CUT_2,
		ANI_HURT,
		ANI_RUN,
		ANI_RUN_ON_FIRE
	};
	LPANIMATION animationIdle,			// animation đứng
		animationRun,					// animation chạy
		animationRunOnFire,				// animation chạy trên lửa
		animationCut_1,					// animation chém 1
		animationCut_2,					// animation chém 2
		animationHurt;					// animation bị đánh

public:
	NormalGuard(float left, float top, float width, float height);

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	
	// Action của enemy béo
	void Cut();							// chém
	void Run();							// chạy
	void Stand();						// đứng
	void Hurt();						// bị đánh
	void Provoke();						// khiêu khích
	void Die();							// chết

	void SetAnimation(NormalGuardAnimations ani);

	// Đổi và reset frame size (khoảng cách để xét va chạm với các obj khác)
	void ChangeFrameSize(GameObject*obj);
	void ResetFrameSize(GameObject*obj);

	// Giao nhau vs Aladdin, táo
	void OnIntersect(GameObject *obj);
	
	~NormalGuard();
};

