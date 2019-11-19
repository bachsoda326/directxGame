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
		NOTMOVING,	// k chuyển động
		FLING,		// quăng ra
		BURST,		// bị vỡ, nát 
		ACTIVED,	// đang xài được
		SPLIT_HALF,	// bị cắt làm đôi
	};

	// Set type va chạm từ obj's id
	void SetObjectFromID();
	// Khởi tạo obj
	void LoadResources();

	/*CCamera *camera;
	void SetCamera(CCamera *camera);*/

	// Process input
	void ProcessInput();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	//collision
	void OnCollision(CGameObject* obj, float normalx, float normaly);
	//interserct
	void OnInterSerct(CGameObject* obj);

	// Hoạt động của táo
	void Move();
	void Burst();	
	void Active();
	void Split_Half();	
	
	//reset
	void ResetProper();

	~CApple();
};

