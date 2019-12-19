#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Aladdin.h"
#include "Item.h"
#include "Stall.h"

class Peddler : public Item
{
private:
	// shop của người bán hàng
	Stall *stall;
	// true: có thể tạo shop | false: k
	bool canCreate;

public:
	enum PeddlerStates
	{
		STANDING,					// đứng
		CREATING,					// đang tạo shop
		DONE						// tạo xong
	};
	enum PeddlerAnimations
	{
		ANI_STAND,
		ANI_CREATE
	};
	LPANIMATION animationStand,		// animation đứng
		animationCreate;			// animation đang tạo shop

public:
	Peddler(float left, float top, float width, float height);

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	// Action của người bán hàng
	void Stand();					// đứng
	void Create();					// đang tạo shop
	void CreateStall();				// tạo shop

	void SetAnimation(PeddlerAnimations ani);

	// Giao nhau vs Aladdin
	void OnIntersect(GameObject *obj);

	~Peddler();
};

