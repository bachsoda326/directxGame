#pragma once
#include "Enemy.h"
#include "FireCarpet.h"
#include "Boss.h"

class FireCarpet;
class Boss;

class Fire : public Enemy
{
private:
	// thảm lửa (vòng boss)
	FireCarpet *fireCarpet;
	Boss *boss;

public:
	enum FireStates
	{
		MOVING,						// di chuyển
		DESTROY						// bị hủy
	};
	enum FireAnimations
	{
		ANI_BURN,					// lửa đốt
		ANI_FIRE					// lửa Boss phun
	};
	LPANIMATION animationBurn,		// animation lửa đốt
		animationFire;				// animation lửa Boss phun

	// 1: lửa đốt của thảm lửa | 2: lửa Boss phun
	int typeFire;

public:
	Fire();	

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	// Action của lửa
	void Move();					// di chuyển
	void Destroy();					// bị hủy

	void SetAnimation(FireAnimations ani);
	// lấy thảm lửa chứa lửa đang xét
	void GetFireCarpet(FireCarpet *obj);
	// lấy Boss
	void GetBoss(Boss*obj);	

	// Va chạm vs đất, cột
	void OnCollision(GameObject *obj, float nx, float ny);
	// Giao nhau với Aladdin
	void OnIntersect(GameObject *obj);

	~Fire();
};

