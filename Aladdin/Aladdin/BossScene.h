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
#include "Boss.h"

class BossScene : public Scene
{
	Grid *grid;
	TileMap *bossMap;
	Aladdin *aladdin = Aladdin::GetInstance();
	Boss *boss;
	Ground *baseGround, *leftPillar, *rightPillar;
	FireCarpet *car1, *car2, *car3, *car4;

	vector<LPGAMEOBJECT> listStaticObjs;
	vector<LPGAMEOBJECT> listEnemies;
	vector<LPGAMEOBJECT> listItems;	
	vector<LPGAMEOBJECT> listOtherObjs;
	vector<LPGAMEOBJECT> coObjects;
public:
	BossScene();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	~BossScene();
};

