#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class Stall : public GameObject
{
private:
	bool canTrade;
public:
	Stall();

	LPANIMATION animationDefault;

	//init object
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Trade();

	void OnIntersect(GameObject *obj);

	~Stall();
};

