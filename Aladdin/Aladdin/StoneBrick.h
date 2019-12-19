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
	LPANIMATION animationDefault;		// animation mặc định

public:
	StoneBrick(float left, float top, float width, float height);	
		
	void LoadResources(bool check);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	
	// lấy bao của gạch đá
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	~StoneBrick();
};

