#pragma once
#include "Aladdin.h"
#include "Collision.h"

class Apple : public GameObject
{
private:	
	bool typeSplit_Half; // true: split_half1, false: split_half2

public:
	Apple();
	Apple(float left, float top, float width, float height);

	LPANIMATION animationItem,
		animationBurst_1,
		animationSplit_Half,
		animationItemActived;

	enum AppleStates
	{
		NOTMOVING,	// k chuyển động
		FLING,		// quăng ra
		BURST,		// bị vỡ, nát 
		ACTIVED,	// được ăn
		SPLIT_HALF	// bị cắt làm đôi
	};

	enum AppleAnimations
	{
		ANI_BURST,		// k chuyển động		
		ANI_SPLIT_HALF,	// bị cắt làm đôi
		ANI_ACTIVED		// được ăn
	};

	// Khởi tạo obj
	void LoadResources();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	
	void SetAnimation(AppleAnimations ani);
		
	// collision
	void OnCollision(GameObject* obj, float nx, float ny);
	// interserct
	void OnIntersect(GameObject* obj);

	void Move();
	void Burst();
	void Active();
	void Split_Half();

	~Apple();
};

