#pragma once
#include "Collision.h"

class Item : public GameObject
{
protected:
	// t.gian bắt đầu đợi
	DWORD startWait;
public:
	enum ItemStates
	{
		NONACTIVED,							// khi chưa đc ăn
		ACTIVED								// khi đc ăn
	};
	LPANIMATION animationItemActived;		// animation item khi đc ăn

public:
	Item();

	virtual void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	// Va chạm (item k xài)
	void OnCollision(GameObject *obj, float nx, float ny);
	// Giao nhau với Aladdin
	void OnIntersect(GameObject *obj);

	// Action khi item
	virtual void Active();					// đc ăn
	virtual void NonActive();				// chưa đc ăn

	~Item();
};

