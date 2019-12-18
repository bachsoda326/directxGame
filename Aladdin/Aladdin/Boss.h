#pragma once
#include "Enemy.h"
#include "Fire.h"
#include "Star.h"

class Fire;
class Star;

class Boss : public Enemy
{
private:
	static Boss * __instance;

	vector<GameObject*>list;	

	DWORD startCut;
	bool isCreate;
	float blood;
	bool isHurt;	

public:
	int typeBoss;

	Boss();
	Boss(float left, float top, float width, float height);
	static Boss * GetInstance();

	LPANIMATION animationMan,
		animationSnake;

	enum BossStates
	{
		STANDING,
		ATTACK,
		DIE
	};

	enum BossAnimations
	{
		ANI_MAN,
		ANI_SNAKE
	};

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	void SetAnimation(BossAnimations ani);

	void Stand();
	void Attack();
	void Die();

	void CreateFire();
	vector<GameObject*>* GetList();
	void DeleteFire(GameObject* fire);
	void CreateStar();
	void DeleteStar(GameObject* star);

	void ChangeFrameSize(GameObject*obj);
	void ResetFrameSize(GameObject*obj);

	void OnCollision(GameObject *obj, float nx, float ny);
	void OnIntersect(GameObject *obj);

	~Boss();
};

