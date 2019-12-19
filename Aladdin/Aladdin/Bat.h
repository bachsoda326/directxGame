#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Enemy.h"

class Bat : public Enemy
{
private:
	// số lượng máu của dơi
	int blood;
	// trạng thái cuối
	int lastState;
public:
	enum BatStates
	{
		STANDING,						// đứng
		PREPARING,						// chuẩn bị tấn công
		ATTACKING,						// tấn công
		HURT,							// bị đánh
		DIEBYAPPLE,						// chết bởi táo
		DIE								// chết
	};
	enum BatAnimations
	{
		ANI_STAND,
		ANI_ATTACK,
		ANI_DIE_BY_APPLE,
		ANI_DIE
	};
	LPANIMATION animationStand,			// animation đứng
		animationAttack,				// animation tấn công
		animationDieByApple;			// animation bị chết bởi táo

public:
	Bat(float left, float top, float width, float height);	

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	// Action của dơi
	void Stand();						// đứng
	void Attack();						// tấn công
	void Hurt();						// bị đánh
	void Die();							// chết

	void SetAnimation(BatAnimations ani);	

	// Đổi và reset frame size (khoảng cách để xét va chạm với các obj khác)
	void ChangeFrameSize(GameObject*obj);
	void ResetFrameSize(GameObject*obj);

	// Giao nhau với Aladdin, táo
	void OnIntersect(GameObject *obj);

	~Bat();
};

