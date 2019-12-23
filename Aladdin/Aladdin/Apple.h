#pragma once
#include "Aladdin.h"
#include "Collision.h"

class Apple : public GameObject
{
private:	
	bool typeSplit_Half; // true: split_half1, false: split_half2
public:
	enum AppleStates
	{
		NOTMOVING,					// k chuyển động
		FLING,						// quăng ra
		BURST,						// bị vỡ, nát 
		ACTIVED,					// được ăn (item)
		SPLIT_HALF					// bị cắt làm đôi (k xài)
	};
	enum AppleAnimations
	{
		ANI_BURST,					// k chuyển động		
		ANI_SPLIT_HALF,				// bị cắt làm đôi (k xài)
		ANI_ACTIVED					// được ăn (item)
	};
	LPANIMATION animationBig,
		animationItem,
		animationBurst_1,
		animationSplit_Half,
		animationItemActived;

public:
	Apple();
	Apple(float left, float top, float width, float height);	
		
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	
	// Action của táo
	void Move();					// hàm mặc định
	void Burst();					// bị vỡ, nát (khi va chạm)
	void Active();					// đc ăn (item)
	void Split_Half();
	void ResetProper();				// reset thuộc tính

	void SetAnimation(AppleAnimations ani);
		
	// Va chạm vs đất, cột
	void OnCollision(GameObject* obj, float nx, float ny);
	// Giao nhau vs các obj còn lại
	void OnIntersect(GameObject* obj);	

	~Apple();
};

