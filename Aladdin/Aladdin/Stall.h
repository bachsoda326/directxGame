#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class Stall : public GameObject
{
private:
	// true: có thể mua | false: k
	bool canTrade;
public:
	LPANIMATION animationDefault;		// animation mặc định

public:
	Stall();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	// Action của shop
	void Trade();

	// Giao nhau vs Aladdin
	void OnIntersect(GameObject *obj);

	~Stall();
};

