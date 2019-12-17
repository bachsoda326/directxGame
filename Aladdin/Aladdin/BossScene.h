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
	Ground *baseGround;

	vector<LPGAMEOBJECT> listPillars;
	vector<LPGAMEOBJECT> listFireCarpets;
	vector<LPGAMEOBJECT> coObjects;
public:
	BossScene();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	void LoadObj(string path);
	void LoadGridObj(string path);

	~BossScene();
};

