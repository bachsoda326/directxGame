#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class BallTrap : public GameObject
{
private:
	// t.gian b.đầu animation
	DWORD startTime;

public:
	BallTrap(float left, float top, float width, float height);

	LPANIMATION animationDefault;
		
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	~BallTrap();
};

