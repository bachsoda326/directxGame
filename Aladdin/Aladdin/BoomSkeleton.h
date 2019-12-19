#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Enemy.h"

class BoomSkeleton : public Enemy
{
private:
	// t.gian b.đầu và h.tại để xóa tự xóa xương đc tạo ra khi bộ xương nổ
	DWORD startTime;
	DWORD currentTime;
	// 0: k mờ | 1: bị mờ
	int isBlink;
	// số lượng máu của bộ xương boom
	int blood;
public:
	enum BoomSkeletonStates
	{
		STANDING,						// đứng
		DOING,							// đang c.bị nổ
		HURT,							// bị đánh
		DIE								// chết
	};
	LPANIMATION animationDefault;		// animation mặc định

public:
	BoomSkeleton(float left, float top, float width, float height);
			
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	// Action của bộ xương boom
	void Stand();						// đứng
	void Doing();						// đang c.bị nổ
	void Hurt();						// bị đánh
	void Die();							// chết
		
	// list xương đc tạo ra
	vector<GameObject*> listBones;
	// lấy list xương
	vector<GameObject*>* GetList();
	// tạo xương
	void CreateBone();
	void DeleteListBones();

	// Đổi và reset frame size (khoảng cách để xét va chạm với các obj khác)
	void ChangeFrameSize(GameObject*obj);
	void ResetFrameSize(GameObject*obj);

	// Giao nhau với Aladdin, táo
	void OnIntersect(GameObject *obj);
	
	~BoomSkeleton();
};

