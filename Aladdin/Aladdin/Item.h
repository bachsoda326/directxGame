#pragma once
#include "Collision.h"

class Item : public GameObject
{
protected:
	DWORD startWait;
public:
	LPANIMATION animationItemActived;

	Item();

	enum ItemStates
	{
		NONACTIVED,
		ACTIVED
	};

	virtual void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void OnCollision(GameObject *obj, float nx, float ny);
	void OnIntersect(GameObject *obj);

	// action when item actived
	virtual void Active();
	virtual void NonActive();

	~Item();
};

