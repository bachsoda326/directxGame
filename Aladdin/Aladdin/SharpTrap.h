#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class SharpTrap : public GameObject
{
private:
	// t.gian b.đầu animation
	DWORD startTime;

public:
	SharpTrap(float left, float top, float width, float height);

	LPANIMATION animationDefault;
	
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	~SharpTrap();
};

