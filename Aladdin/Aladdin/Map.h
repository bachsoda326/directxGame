#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Camera.h"
#include "Game.h"

class Map : public GameObject
{
	Sprite *sprite;
public:
	Map(int idMap);
	~Map();

	/*Camera *camera;
	void SetCamera(Camera *camera);*/

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
};

