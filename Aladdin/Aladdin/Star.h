#pragma once
#include "Boss.h"
#include "Aladdin.h"

class Boss;

class Star: public GameObject
{
private:
	Boss *boss;
public:
	enum StarStates
	{
		FLING,							// bay
		DESTROY							// hủy
	};
	enum StarAnimations
	{
		ANI_FLING,
		ANI_DESTROY
	};
	LPANIMATION animationFling,			// animation khi bay
		animationDestroy;				// animation khi trúng Aladdin

public:
	Star();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	// Action của sao
	void Destroy();						// hủy
	void Fly();							// bay
		
	void SetAnimation(StarAnimations ani);
	// lấy Boss
	void GetBoss(Boss *obj);

	// Va chạm (k xài)
	void OnCollision(GameObject *obj, float nx, float ny);
	// Giao nhau vs Aladdin
	void OnIntersect(GameObject *obj);

	~Star();
};

