#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	LPANIMATION animationDie;		// animation chết

public:
	Enemy();	

	void LoadResources();

	// Action của enemy
	void Die();						// chết

	~Enemy();
};

