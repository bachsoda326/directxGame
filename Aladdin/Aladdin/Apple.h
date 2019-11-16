#pragma once
#include "Aladdin.h"

class CApple : public CGameObject
{
private:	
	bool typeSplit_Half; // true: split_half1, false: split_half2

public:
	CApple();

	LPANIMATION currentAnimation,
		animationBurst_1,
		animationSplit_Half;

	enum AppleStates
	{
		NOTMOVING,
		FLING,
		BURST,
		ACTIVED,
		SPLIT_HALF,
	};

	//set type collision from object's id
	void SetObjectFromID();
	//init object
	void LoadResources();

	/*CCamera *camera;
	void SetCamera(CCamera *camera);*/

	//process input
	void ProcessInput();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	//collision
	void OnCollision(CGameObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(CGameObject* obj);

	//action of apple
	void Move();
	void Burst();	
	void Active();
	void Split_Half();	
	
	//reset
	void ResetProper();

	~CApple();
};

