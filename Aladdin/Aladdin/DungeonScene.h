#pragma once
#include "Scene.h"
#include "Grid.h"
#include "TileMap.h"
#include "BloodBar.h"
#include "StoneBrick.h"
#include "AladdinFace.h"
#include "Ground.h"

class DungeonScene : public Scene
{
public:
	Grid *grid;
	TileMap *map, *frontMap;
	Aladdin *aladdin = Aladdin::GetInstance();
	BloodBar *bloodBar;
	AladdinFace *face;
	Ground *baseGround;

	vector<GameObject*> listStaticObjs;
	vector<GameObject*> listEnemies;
	vector<GameObject*> listItems;
	vector<StoneBrick*> listStoneBricks;
	vector<GameObject*> listOtherObjs;

public:
	DungeonScene();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	void LoadStaticObj(string path);
	void LoadObj(string path);
	void LoadGridStaticObj(string path);
	void LoadGridObj(string path);

	~DungeonScene();
};

