#pragma once
#include <algorithm>
#include "GameObject.h"

class Collision
{
public:
	//contructor of SweptAABB
	Collision();

	//check collision between 2 GameObject(retangle)
	static float SweptAABB(GameObject* obj1, GameObject* obj2, float& nx, float& ny);
	static void ExceptionalCase(GameObject* obj1, GameObject* obj2, float& nx, float& ny, float& collisionTime);
	static void FilterCollision(float &t, float &nx, float &ny, float dnx, float dny);

	//check broad-phasing
	static GameObject* GetSweptBroadphaseBaseObject(GameObject* obj);

	//check AABB
	static bool AABBCheck(GameObject* obj1, GameObject* obj2);

	//check collision
	static void CheckCollision(GameObject* obj1, GameObject* obj2);
	static void PreventMove(GameObject* obj1, GameObject* obj2, float nx, float ny);
	static void CollisionLine(GameObject* obj1, GameObject* obj2, float nx, float ny);

	//destructor of SweptAABB
	~Collision();
};

