#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class Abu : public GameObject
{
private:
	static Abu * __instance;

public:
	int beginStat;

	Abu();
	static Abu * GetInstance();

	LPANIMATION animationFan,
		animationRun;

	enum AbuStates
	{
		FAN,
		RUN
	};

	enum AbuAnimations
	{
		ANI_FAN,
		ANI_RUN
	};

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	
	void SetAnimation(AbuAnimations ani);

	void Fan();
	void Run();

	~Abu();
};

