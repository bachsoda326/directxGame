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
private:
	Grid *grid;
	// map nền
	TileMap *bossMap;
	Aladdin *aladdin = Aladdin::GetInstance();
	Boss *boss = Boss::GetInstance();
	// nền đất
	Ground *baseGround;
	// biến để tạo táo mỗi khi Aladdin ném hết táo; true: tạo đc | false: k tạo đc
	bool canCreateApple;

	// list cột (2 cột trái phải)
	vector<LPGAMEOBJECT> listPillars;
	// list thảm lửa (4 cái), k có lửa khi Boss là người
	vector<LPGAMEOBJECT> listFireCarpets;
	// list táo bên thảm lửa trái
	vector<LPGAMEOBJECT> listLeftApples;
	// list táo bên thảm lửa phải
	vector<LPGAMEOBJECT> listRightApples;
	// list obj nằm trong vùng camera
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

