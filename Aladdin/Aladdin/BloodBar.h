#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class BloodBar : public GameObject
{
private:
	DWORD lastTime, startBlink;

	// giống nhấp nháy (blink) của aladdin
	int isBlink;
	int oldBlood;

public:
	//contructor of BloodBar class
	BloodBar();

	LPANIMATION animationDefault;

	//init object
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	//process input
	virtual void ProcessInput();	

	~BloodBar();	
};

