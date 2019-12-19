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
	LPANIMATION animationDefault;		// animation mặc định

public:
	SharpTrap(float left, float top, float width, float height);
	
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	~SharpTrap();
};

