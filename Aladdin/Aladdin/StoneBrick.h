#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class StoneBrick : public GameObject
{
private:
	// t.gian b.đầu animation
	DWORD startTime;

public:
	StoneBrick(float left, float top, float width, float height);

	LPANIMATION animationDefault;		
		
	void LoadResources(bool check);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	~StoneBrick();
};

