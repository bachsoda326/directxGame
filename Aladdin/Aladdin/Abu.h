#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class Abu : public GameObject
{
private:
	static Abu * __instance;
public:	
	enum AbuStates
	{
		FAN,						// quạt
		RUN							// chạy
	};
	enum AbuAnimations
	{
		ANI_FAN,
		ANI_RUN
	};
	LPANIMATION animationFan,		// animation quạt
		animationRun;				// animation chạy

	// 0: chạy | 1: quạt
	int beginStat;

public:
	Abu();
	static Abu * GetInstance();		

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	// Action của khỉ Abu
	void Fan();						// quạt
	void Run();						// chạy

	void SetAnimation(AbuAnimations ani);
	~Abu();
};

