#include "DungeonScene.h"
#include <fstream>
#include <sstream>
#include "Chains.h"
#include "Apple.h"
#include "Peddler.h"
#include "Ruby.h"
#include "BlueHeart.h"
#include "GenieFace.h"
#include "GenieJar.h"
#include "Bat.h"
#include "NormalGuard.h"
#include "ThinGuard.h"
#include "BoomSkeleton.h"
#include "SharpTrap.h"
#include "BallTrap.h"

DungeonScene::DungeonScene()
{
	GameSound::getInstance()->play(GAME1_MUSIC, true);
}

void DungeonScene::LoadResources()
{
	Scene::LoadResources();

	grid = new Grid(MAP_WIDTH, MAP_HEIGHT, 150);

	LoadStaticObj("txt\\Ground_obj.txt");
	LoadObj("txt\\Obj_obj.txt");
	LoadGridStaticObj("txt\\Ground_grid.txt");
	LoadGridObj("txt\\Obj_grid.txt");

	map = new TileMap();
	map->LoadTileMap(ID_TEX_TILESHEET_MAP, TEX_TILESHEET_MAP_PATH, TXT_TILEMAP_MAP_PATH);
	frontMap = new TileMap();
	frontMap->LoadTileMap(ID_TEX_TILESHEET_FRONTMAP, TEX_TILESHEET_FRONTMAP_PATH, TXT_TILEMAP_FRONTMAP_PATH);

	aladdin->LoadResources();
	aladdin->SetPosition(1000, 1006);
	//aladdin->SetPosition(950, 587);	// error fence climb_jump
	/*aladdin->SetPosition(250, 480);*/		// peddler
	//aladdin->SetPosition(ALADDIN_POTISION_X, ALADDIN_POTISION_Y);
	//aladdin->SetCamera::GetInstance()(Camera::GetInstance());	

	bloodBar = new BloodBar();
	bloodBar->SetPosition(0, 10);
	bloodBar->LoadResources();

	face = new AladdinFace();
	face->SetPosition(10, 220);
	face->LoadResources();

	aladdinApple = new Apple();
	aladdinApple->collType = CollUnknown;
	aladdinApple->SetPosition(317, 230);
	aladdinApple->LoadResources();

	aladdinRuby = new Ruby();
	aladdinRuby->collType = CollUnknown;
	aladdinRuby->SetPosition(280, 230);
	aladdinRuby->LoadResources();

	baseGround = new Ground(0, 1112, 2270, 27);
	baseGround->collType = CollGround;
	basePillar = new Ground(1489, 402, 80, 740);
	basePillar->collType = CollFence;

	for (int i = 0; i < listStoneBricks.size(); i += 2)
	{
		listStoneBricks[i]->LoadResources(true);
		//grid->AddObjToCell(listStoneBricks[i]);		
	}
	for (int i = 1; i < listStoneBricks.size(); i += 2)
	{
		listStoneBricks[i]->LoadResources(false);
		//grid->AddObjToCell(listStoneBricks[i]);
	}
	for (int i = 0; i < listItems.size(); i++)
	{
		listItems[i]->LoadResources();
		//grid->AddObjToCell(listItems[i]);
	}
	for (int i = 0; i < listEnemies.size(); i++)
	{
		listEnemies[i]->LoadResources();
		//grid->AddObjToCell(listEnemies[i]);
	}
	for (int i = 0; i < listOtherObjs.size(); i++)
	{
		listOtherObjs[i]->LoadResources();
		//grid->AddObjToCell(listOtherObjs[i]);
	}
}

void DungeonScene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Scene::Update(dt);

	vector<LPGAMEOBJECT> coObjs;
	coObjs.push_back(baseGround);
	coObjs.push_back(basePillar);
	grid->CalcColliableObjs(Camera::GetInstance(), coObjs);

	//aladdin->HandleKeyBoard();	
	aladdin->Update(dt);
	bloodBar->Update(dt);

	aladdin->nx = 0;
	aladdin->ny = 0;
	for (int i = 0; i < coObjs.size(); i++)
	{
		Collision::CheckCollision(aladdin, coObjs[i]);
		coObjs[i]->Update(dt);
		for (int j = 0; j < aladdin->GetListApples()->size(); j++)
		{
			Collision::CheckCollision(aladdin->GetListApples()->at(j), coObjs[i]);
		}
	}
	for (int i = 0; i < Aladdin::GetInstance()->GetListApples()->size(); i++)
		Aladdin::GetInstance()->GetListApples()->at(i)->ProcessInput();
	Collision::CheckCollision(aladdin, baseGround);

	//aladdin->CheckCollision(&coObjs);
}

void DungeonScene::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = Game::GetInstance()->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 0.0f, 0);

	if (d3ddv->BeginScene())
	{
		vector<LPGAMEOBJECT> coObjects;
		coObjects.push_back(baseGround);
		coObjects.push_back(basePillar);
		grid->CalcColliableObjs(Camera::GetInstance(), coObjects);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		map->Render();
		for (int i = 0; i < coObjects.size(); i++)
		{
			coObjects[i]->Render();
		}
		aladdin->Render();
		frontMap->Render();
		bloodBar->Render();
		face->Render();
		aladdinApple->Render();
		aladdinRuby->Render();

		spriteHandler->End();

		DrawFont(score, 280, 10, 35, 25, Aladdin::GetInstance()->score);
		DrawFont(numLifes, 35, 230, 35, 25, Aladdin::GetInstance()->numLifes);
		DrawFont(numRubies, 285, 230, 35, 25, Aladdin::GetInstance()->numRubies);
		DrawFont(numApples, 318, 230, 35, 25, Aladdin::GetInstance()->numApples);
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(0, 0, 0, 0);
}

void DungeonScene::LoadStaticObj(string path)
{
	GameObject *objGround = 0;

	fstream fs;
	fs.open(path);

	int numObjs = 0;
	fs >> numObjs;

	int index;
	string name;
	int xDraw, yDraw, width, height;

	for (int i = 0; i < numObjs; i++)
	{
		fs >> index;
		fs >> name;
		fs >> xDraw;
		fs >> yDraw;
		fs >> width;
		fs >> height;

		if (name == "StoneBar" || name == "Wood")
		{
			objGround = new Ground(xDraw, yDraw, width, height);
			objGround->id = index;
			objGround->collType = CollGround;
		}
		else if (name == "Fence")
		{
			objGround = new Ground(xDraw, yDraw, width, height);
			objGround->id = index;
			objGround->collType = CollFence;
		}
		else if (name == "Chains")
		{
			objGround = new Chains(xDraw, yDraw, width, height);
			objGround->id = index;
		}

		listStaticObjs.push_back(objGround);
	}

	fs.close();
}

void DungeonScene::LoadObj(string path)
{
	GameObject *obj = 0;
	StoneBrick *stoneBrick = 0;

	fstream fs;
	fs.open(path);

	int numObjs = 0;
	fs >> numObjs;

	int index;
	string name;
	int xDraw, yDraw, width, height;

	for (int i = 0; i < numObjs; i++)
	{
		fs >> index;
		fs >> name;
		fs >> xDraw;
		fs >> yDraw;
		fs >> width;
		fs >> height;

		if (name == "AppleItem")
		{
			obj = new Apple(xDraw, yDraw, width, height);
			obj->id = index;
			obj->collType = CollItem;
			listItems.push_back(obj);
		}
		else if (name == "Peddler")
		{
			obj = new Peddler(xDraw, yDraw, width, height);
			obj->id = index;
			listItems.push_back(obj);
		}
		else if (name == "Ruby")
		{
			obj = new Ruby(xDraw, yDraw, width, height);
			obj->id = index;
			listItems.push_back(obj);
		}
		else if (name == "BlueHeart")
		{
			obj = new BlueHeart(xDraw, yDraw, width, height);
			obj->id = index;
			listItems.push_back(obj);
		}
		else if (name == "GenieFace")
		{
			obj = new GenieFace(xDraw, yDraw, width, height);
			obj->id = index;
			listItems.push_back(obj);
		}
		else if (name == "GenieJar")
		{
			obj = new GenieJar(xDraw, yDraw, width, height);
			obj->id = index;
			listItems.push_back(obj);
		}
		else if (name == "Bat")
		{
			obj = new Bat(xDraw, yDraw, width, height);
			obj->id = index;
			listEnemies.push_back(obj);
		}
		else if (name == "NormalGuard")
		{
			obj = new NormalGuard(xDraw, yDraw, width, height);
			obj->id = index;
			listEnemies.push_back(obj);
		}
		else if (name == "ThinGuard")
		{
			obj = new ThinGuard(xDraw, yDraw, width, height);
			obj->id = index;
			listEnemies.push_back(obj);
		}
		else if (name == "BoomSkeleton")
		{
			obj = new BoomSkeleton(xDraw, yDraw, width, height);
			obj->id = index;
			listEnemies.push_back(obj);
		}
		else if (name == "StoneBrick")
		{
			stoneBrick = new StoneBrick(xDraw, yDraw, width, height);
			stoneBrick->id = index;
			listStoneBricks.push_back(stoneBrick);
		}
		else if (name == "SharpTrap")
		{
			obj = new SharpTrap(xDraw, yDraw, width, height);
			obj->id = index;
			listOtherObjs.push_back(obj);
		}
		else if (name == "BallTrap")
		{
			obj = new BallTrap(xDraw, yDraw, width, height);
			obj->id = index;
			listOtherObjs.push_back(obj);
		}
	}

	fs.close();
}

void DungeonScene::LoadGridStaticObj(string path)
{
	GameObject *objGround = 0;

	fstream fs;
	fs.open(path);

	/*int numCells = 0;
	fs >> numCells;*/

	int cellIndex = 0;;
	int objIndex = 0;

	string line;					// dòng 1
	while (getline(fs, line))
	{
		istringstream iss(line);	// tạo 1 string stream từ dòng 1	
		vector<int> listId;
		for (int n; iss >> n;)		// đọc số nguyên từ stream vào mảng a
			listId.push_back(n);

		cellIndex = listId[0];
		for (int i = 1; i < listId.size(); i++)
		{
			//DebugOut(L"[COLL] collision: %d\n", listId[0]);
			objIndex = listId[i];
			for (int t = 0; t < listStaticObjs.size(); t++)
			{
				if (listStaticObjs[t]->id == objIndex)
				{
					grid->AddObjToCell(cellIndex, listStaticObjs[t]);
					break;
				}
			}
		}
	}

	fs.close();
}

void DungeonScene::LoadGridObj(string path)
{
	GameObject *objGround = 0;

	fstream fs;
	fs.open(path);

	/*int numCells = 0;
	fs >> numCells;*/

	int cellIndex = 0;;
	int objIndex = 0;

	string line;					// dòng 1
	while (getline(fs, line))
	{
		istringstream iss(line);	// tạo 1 string stream từ dòng 1	
		vector<int> listId;
		for (int n; iss >> n;)		// đọc số nguyên từ stream vào mảng a
			listId.push_back(n);

		cellIndex = listId[0];
		for (int i = 1; i < listId.size(); i++)
		{
			// biến k.tra xem đã thêm obj với objIndex đang xét chưa, true thì xét objIndex mới tiếp
			bool isAdded = false;

			objIndex = listId[i];
			for (int t = 0; t < listItems.size(); t++)
			{
				if (isAdded == true) break;
				if (listItems[t]->id == objIndex)
				{
					grid->AddObjToCell(cellIndex, listItems[t]);
					isAdded = true;
					break;
				}
			}
			for (int t = 0; t < listEnemies.size(); t++)
			{
				if (isAdded == true) break;
				if (listEnemies[t]->id == objIndex)
				{
					grid->AddObjToCell(cellIndex, listEnemies[t]);
					isAdded = true;
					break;
				}
			}
			for (int t = 0; t < listStoneBricks.size(); t++)
			{
				if (isAdded == true) break;
				if (listStoneBricks[t]->id == objIndex)
				{
					grid->AddObjToCell(cellIndex, listStoneBricks[t]);
					isAdded = true;
					break;
				}
			}
			for (int t = 0; t < listOtherObjs.size(); t++)
			{
				if (isAdded == true) break;
				if (listOtherObjs[t]->id == objIndex)
				{
					grid->AddObjToCell(cellIndex, listOtherObjs[t]);
					isAdded = true;
					break;
				}
			}
		}
	}

	fs.close();
}

DungeonScene::~DungeonScene()
{
}
