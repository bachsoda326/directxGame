#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy();
	
	LPANIMATION animationDie;

	void LoadResources();
	//void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Die();

	~Enemy();
};

