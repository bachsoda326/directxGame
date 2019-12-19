#pragma once
#include "Scene.h"
#include "Grid.h"
#include "TileMap.h"
#include "BloodBar.h"
#include "StoneBrick.h"
#include "AladdinFace.h"
#include "Ground.h"
#include "Apple.h"
#include "Ruby.h"

class DungeonScene : public Scene
{
public:
	Grid *grid;
	// map nền, map cột
	TileMap *map, *frontMap;
	Aladdin *aladdin = Aladdin::GetInstance();
	// nền đất, trụ to
	Ground *baseGround, *basePillar;

	vector<LPGAMEOBJECT> listObjs;
	// list obj tĩnh (đất, hàng rào, dây xích)
	vector<LPGAMEOBJECT> listStaticObjs;	
	// list gạch đá
	vector<StoneBrick*> listStoneBricks;
	// list obj nằm trong vùng camera
	vector<LPGAMEOBJECT> coObjects;

public:
	DungeonScene();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	// Load obj tĩnh
	void LoadStaticObj(string path);
	// Load obj còn lại
	void LoadObj(string path);
	void LoadGridStaticObj(string path);
	void LoadGridObj(string path);

	~DungeonScene();
};

