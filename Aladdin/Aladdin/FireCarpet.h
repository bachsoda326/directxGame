#pragma once
#include "Collision.h"
#include "Fire.h"

class Fire;

class FireCarpet : public GameObject
{
private:
	DWORD lastTime, startDelay;
	vector<GameObject*> listFires;

public:
	FireCarpet();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	void CreateFire(GameObject *obj);
	vector<GameObject*>* GetListFires();
	void DeleteFire(GameObject *sword);

	void OnCollision(GameObject *obj, float nx, float ny);
	void OnIntersect(GameObject *obj);

	~FireCarpet();
};

