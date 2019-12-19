#pragma once
#include "Collision.h"
#include "Fire.h"

class Fire;

class FireCarpet : public GameObject
{
private:
	// t.gian trễ khi tạo lửa lúc Aladdin đứng lên thảm lửa
	DWORD lastTime, startDelay;
	// list lửa của thảm
	vector<GameObject*> listFires;

public:
	FireCarpet(float left, float top, float width, float height);

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	// tạo lửa
	void CreateFire(GameObject *obj);
	// lấy list lửa
	vector<GameObject*>* GetList();
	void DeleteFire(GameObject *sword);

	// Va chạm (k xài)
	void OnCollision(GameObject *obj, float nx, float ny);
	// Giao nhau với Aladdin
	void OnIntersect(GameObject *obj);

	~FireCarpet();
};

