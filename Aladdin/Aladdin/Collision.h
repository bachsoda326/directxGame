#pragma once
#include <algorithm>
#include "GameObject.h"

class Collision
{
public:	
	Collision();

	static float SweptAABB(GameObject* obj1, GameObject* obj2, float& nx, float& ny);
	// Trường hợp ngoại lệ của va chạm, trả về collisionTime
	static void ExceptionalCase(GameObject* obj1, GameObject* obj2, float& nx, float& ny, float& collisionTime);
	// check broad-phasing
	static GameObject* GetSweptBroadphaseBaseObject(GameObject* obj);
	// Kiểm tra 2 bao obj có đụng nhau k
	static bool AABBCheck(GameObject* obj1, GameObject* obj2);

	// Check collision 2 obj
	static void CheckCollision(GameObject* obj1, GameObject* obj2);
	// Ngăn di chuyển
	static void PreventMove(GameObject* obj1, GameObject* obj2, float nx, float ny);
	
	~Collision();
};

