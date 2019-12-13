#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Enemy.h"

class BoomSkeleton : public Enemy
{
private:
	DWORD startTime;
	DWORD currentTime;
	// số lượng máu của boom skeleton
	int blood;

public:
	BoomSkeleton(float left, float top, float width, float height);

	LPANIMATION animationDefault;

	enum BoomSkeletonStates
	{
		STANDING,
		DOING,
		HURT,
		DIE
	};
		
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	// Action	
	void Stand();
	void Doing();
	void Hurt();
	void Die();

	// Handle bone
	vector<GameObject*> listBones;
	vector<GameObject*>* GetListBones();
	void CreateBone();
	void DeleteListBones();
	void DeleteBone(GameObject *bone);

	// Change and reset frame size
	void ChangeFrameSize(GameObject*obj);
	void ResetFrameSize(GameObject*obj);

	void OnIntersect(GameObject *obj);
	
	~BoomSkeleton();
};

