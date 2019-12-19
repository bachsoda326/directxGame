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

	// List chứa sao và lửa đc tạo ra bởi Boss
	vector<GameObject*>list;		
	// t.gian trễ để tạo sao
	DWORD startCut;
	// dùng cho tạo lửa; true: đã tạo | false: chưa tạo
	bool isCreate;
	// máu của Boss
	float blood;
	// true: bị đánh | false: chưa bị đánh
	bool isHurt;	
public:
	enum BossStates
	{
		STANDING,					// đứng
		ATTACK,						// tấn công
		DIE							// chết
	};
	enum BossAnimations
	{
		ANI_MAN,					// người
		ANI_SNAKE					// rắn
	};
	LPANIMATION animationMan,		// animation người
		animationSnake;				// animation rắn

	// 0: người | 1: rắn
	int typeBoss;

public:
	Boss();
	Boss(float left, float top, float width, float height);
	static Boss * GetInstance();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	// Action của Boss
	void Stand();					// đứng
	void Attack();					// tấn công
	void Die();						// chết

	void SetAnimation(BossAnimations ani);	

	vector<GameObject*>* GetList();
	// Tạo sao
	void CreateStar();
	void DeleteStar(GameObject* star);
	// Tạo lửa
	void CreateFire();	
	void DeleteFire(GameObject* fire);	

	// Đổi và reset frame size (khoảng cách để xét va chạm với các obj khác)
	void ChangeFrameSize(GameObject*obj);
	void ResetFrameSize(GameObject*obj);

	// Va chạm (k xài)
	void OnCollision(GameObject *obj, float nx, float ny);
	// Giao nhau vs Aladdin, táo
	void OnIntersect(GameObject *obj);

	~Boss();
};

