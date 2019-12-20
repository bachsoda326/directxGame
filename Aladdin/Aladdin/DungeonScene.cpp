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
#include "SceneManager.h"
#include "NextScene.h"

DungeonScene::DungeonScene()
{
	GameSound::getInstance()->play(GAME1_MUSIC, true);
	LoadResources();
}

void DungeonScene::LoadResources()
{	
	grid = new Grid(MAP_WIDTH, MAP_HEIGHT, CELL_SIZE);

	LoadStaticObj("txt\\Ground_obj.txt");
	LoadObj("txt\\Obj_obj.txt");
	LoadGridStaticObj("txt\\Ground_grid.txt");
	LoadGridObj("txt\\Obj_grid.txt");

	map = new TileMap();
	map->LoadTileMap(ID_TEX_TILESHEET_MAP, TEX_TILESHEET_MAP_PATH, TXT_TILEMAP_MAP_PATH);
	frontMap = new TileMap();
	frontMap->LoadTileMap(ID_TEX_TILESHEET_FRONTMAP, TEX_TILESHEET_FRONTMAP_PATH, TXT_TILEMAP_FRONTMAP_PATH);
		
	aladdin->SetPosition(ALADDIN_POTISION_X, ALADDIN_POTISION_Y);
	//aladdin->SetPosition(1039, 790);
	//aladdin->SetPosition(2000, 200);
	//aladdin->SetPosition(950, 587);		// error fence climb_jump
	/*aladdin->SetPosition(250, 480);*/		// peddler		

	baseGround = new Ground(0, 1112, 2270, 27);
	baseGround->collType = CollGround;
	basePillar = new Ground(1489, 402, 80, 740);
	basePillar->collType = CollFence;

	for (int i = 0; i < listObjs.size(); i ++)
	{
		listObjs[i]->LoadResources();		
	}
	for (int i = 0; i < listStoneBricks.size(); i += 2)
	{
		listStoneBricks[i]->LoadResources(true);		
	}
	for (int i = 1; i < listStoneBricks.size(); i += 2)
	{
		listStoneBricks[i]->LoadResources(false);		
	}	
}

void DungeonScene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjs)
{	
	UpdateCamera(CAMERA_MAP_WIDTH, CAMERA_MAP_HEIGHT);
	//DebugOut("[SIZE]: %d\n", coObjects.size());
	coObjects.clear();
	coObjects.push_back(baseGround);
	coObjects.push_back(basePillar);
	// tính toán những obj nằm trong vùng camera rồi đưa vào list coObjects
	grid->CalcColliableObjs(Camera::GetInstance(), coObjects);

	// nếu obj đã chết thì xóa obj khỏi grid, listObjs và list coObjects
	for (int i = 0; i < coObjects.size(); i++)
	{
		if (coObjects[i]->isDead)
		{			
			for (int t = 0; t < listObjs.size(); t++)
			{				
				if (listObjs[t] == coObjects[i])
				{
					int cellIndex = listObjs[t]->cellIndex;
					for (int k = 0; k < grid->listCells[cellIndex].listObj.size(); k++)
					{
						if (grid->listCells[cellIndex].listObj[k] == listObjs[t])
						{
							grid->listCells[cellIndex].listObj.erase(grid->listCells[cellIndex].listObj.begin() + k);
							break;
						}
					}
					listObjs.erase(listObjs.begin() + t);
					break;
				}
			}			
			coObjects.erase(coObjects.begin() + i);
		}
	}
		
	aladdin->Update(dt);
	Scene::Update(dt);

	// set lại gía trị va chạm nx, ny của Aladdin
	aladdin->nx = 0;
	aladdin->ny = 0;
	for (int i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Update(dt);
		// va chạm Aladdin vs các obj
		Collision::CheckCollision(aladdin, coObjects[i]);
		// va chạm táo của Aladdin vs các obj
		for (int j = 0; j < aladdin->GetList()->size(); j++)
		{
			Collision::CheckCollision(aladdin->GetList()->at(j), coObjects[i]);
		}
	}
	
	// k.tra Aladdin ở vị trí chuyển màn
	if (aladdin->x >= MAP_PASS_X && aladdin->y <= MAP_PASS_Y)
	{
		SceneManager::GetInstance()->ReplaceScene(new NextScene(3));
		return;
	}
}

void DungeonScene::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = Game::GetInstance()->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();

	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 0.0f, 0);

	if (d3ddv->BeginScene())
	{
		coObjects.clear();		
		// tính toán những obj nằm trong vùng camera rồi đưa vào list coObjects
		grid->CalcColliableObjs(Camera::GetInstance(), coObjects);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		if (aladdin->isDead)
		{
			GameSound::getInstance()->stop(GAME1_MUSIC);
			return;
		}
		if (!aladdin->isDie)
		{
			map->Render(Camera::GetInstance());
			for (int i = 0; i < coObjects.size(); i++)
			{
				coObjects[i]->Render();
			}
			aladdin->Render();
			frontMap->Render(Camera::GetInstance());
			Scene::Render();
		}
		else
		{
			Abu::GetInstance()->Render();
			aladdin->Render();
			Scene::Render();
		}

		spriteHandler->End();
		DrawFonts();
		d3ddv->EndScene();
	}

	// display back buffer content to the screen
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
		}
		else if (name == "Peddler")
		{
			obj = new Peddler(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		else if (name == "Ruby")
		{
			obj = new Ruby(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		else if (name == "BlueHeart")
		{
			obj = new BlueHeart(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		else if (name == "GenieFace")
		{
			obj = new GenieFace(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		else if (name == "GenieJar")
		{
			obj = new GenieJar(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		else if (name == "Bat")
		{
			obj = new Bat(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		else if (name == "NormalGuard")
		{
			obj = new NormalGuard(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		else if (name == "ThinGuard")
		{
			obj = new ThinGuard(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		else if (name == "BoomSkeleton")
		{
			obj = new BoomSkeleton(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		else if (name == "StoneBrick")
		{
			stoneBrick = new StoneBrick(xDraw, yDraw, width, height);
			stoneBrick->id = index;
			listStoneBricks.push_back(stoneBrick);
			continue;
		}
		else if (name == "SharpTrap")
		{
			obj = new SharpTrap(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		else if (name == "BallTrap")
		{
			obj = new BallTrap(xDraw, yDraw, width, height);
			obj->id = index;			
		}
		listObjs.push_back(obj);
	}

	fs.close();
}

void DungeonScene::LoadGridStaticObj(string path)
{	
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
					// thêm obj vào cell của grid
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
			for (int t = 0; t < listStoneBricks.size(); t++)
			{
				if (isAdded == true) break;
				if (listStoneBricks[t]->id == objIndex)
				{
					// thêm obj vào cell của grid
					grid->AddObjToCell(cellIndex, listStoneBricks[t]);
					isAdded = true;
					break;
				}
			}
			for (int t = 0; t < listObjs.size(); t++)
			{
				if (isAdded == true) break;
				if (listObjs[t]->id == objIndex)
				{
					// thêm obj vào cell của grid
					grid->AddObjToCell(cellIndex, listObjs[t]);
					listObjs[t]->cellIndex = cellIndex;
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