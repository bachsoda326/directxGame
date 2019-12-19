#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"

class BloodBar : public GameObject
{
private:
	// t.gian bắt đầu mờ
	DWORD startBlink;
	// 0: k mờ | 1: bị mờ
	int isBlink;
	int oldBlood;
public:
	LPANIMATION animationDefault;		// animation mặc định

public:	
	BloodBar();	
	
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	~BloodBar();	
};

