/* =============================================================
INTRODUCTION TO GAME PROGRAMMING SE102

SAMPLE 04 - COLLISION

This sample illustrates how to:

1/ Implement SweptAABB algorithm between moving objects
2/ Implement a simple (yet effective) collision frame work

Key functions:
Game::SweptAABB
GameObject::SweptAABBEx
GameObject::CalcPotentialCollisions
GameObject::FilterCollision

GameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Map.h"
#include "Constants.h"
#include "Textures.h"
#include "Grid.h"
#include "Aladdin.h"
#include "AladdinFace.h"
#include "BloodBar.h"
# include "Ground.h"
#include "Chains.h"
#include "TileMap.h"
#include "Apple.h"
#include "Ruby.h"
#include "BlueHeart.h"
#include "GenieFace.h"
#include "GenieJar.h"
#include "Bat.h"
#include "NormalGuard.h"
#include "ThinGuard.h"
#include "BoomSkeleton.h"
#include "Peddler.h"
#include "StoneBrick.h"
#include "SharpTrap.h"
#include "BallTrap.h"

Game *game;
Camera *camera = Camera::GetInstance();
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

vector<LPGAMEOBJECT> objects;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadStaticObj(string path)
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

void LoadObj(string path)
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

void LoadGridStaticObj(string path)
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

void LoadGridObj(string path)
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

// Kiểm tra camera khi chạm biên map và đặt vị trí camera theo Aladdin
void CheckCameraAndWorldMap()
{
	// test Camera move when Mario is not on center screen
	//mCamera->SetPosition(mPlayer->GetPosition() + D3DXVECTOR3(100,0,0));
	camera->SetPosition(aladdin->GetPosition());

	if (camera->GetBound().left < 0)
	{
		//vi position cua camera ma chinh giua camera
		//luc nay o vi tri goc ben trai cua the gioi thuc
		camera->SetPosition(camera->GetWidth() / 2, camera->GetPosition().y);
	}

	if (camera->GetBound().right > CAMERA_MAP_WIDTH)
	{
		//luc nay cham goc ben phai cua the gioi thuc
		camera->SetPosition(CAMERA_MAP_WIDTH - camera->GetWidth() / 2,
			camera->GetPosition().y);
	}

	if (camera->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		camera->SetPosition(camera->GetPosition().x, camera->GetHeight() / 2);
	}

	if (camera->GetBound().bottom > CAMERA_MAP_HEIGHT)
	{
		//luc nay cham day cua the gioi thuc
		camera->SetPosition(camera->GetPosition().x,
			CAMERA_MAP_HEIGHT - camera->GetHeight() / 2);
	}
}

/*
Load all game resources
In this example: load textures, sprites, animations and s.t object

TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	Textures * textures = Textures::GetInstance();

	// tạo texture lớn từ đường dẫn và add vào instance"textures"
	textures->Add(ID_TEX_ALADDIN, TEX_ALADDIN_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM, TEX_ITEMS_PATH, D3DCOLOR_XRGB(248, 0, 248));
	textures->Add(ID_TEX_PEDDLER, TEX_PEDDLER_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BRICK_TRAP, TEX_BRICK_TRAP_PATH, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_GUARDS, TEX_GUARDS_PATH, D3DCOLOR_XRGB(120, 193, 152));
	textures->Add(ID_TEX_BAT, TEX_BAT_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BOOMSKELETON, TEX_BOOMSKELETON_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ENEMYDEAD, TEX_ENEMYDEAD_PATH, D3DCOLOR_XRGB(186, 254, 202));
	textures->Add(ID_TEX_ENEMYEXPLOSION, TEX_ENEMYEXPLOSION_PATH, D3DCOLOR_XRGB(186, 254, 202));
	textures->Add(ID_TEX_ITEMACTIVED, TEX_ITEMACTIVED_PATH, D3DCOLOR_XRGB(255, 4, 253));
	textures->Add(ID_TEX_BLOODBAR, TEX_BLOODBAR_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, TEX_BBOX_PATH, D3DCOLOR_XRGB(255, 255, 255));

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
	//aladdin->SetPosition(1170, 270);
	aladdin->SetPosition(1600, 950);
	//aladdin->SetCamera(camera);	
	
	bloodBar = new BloodBar();
	bloodBar->SetPosition(0, 10);
	bloodBar->LoadResources();

	face = new AladdinFace();
	face->SetPosition(10, 220);
	face->LoadResources();

	baseGround = new Ground(0, 1112, 2270, 27);
	baseGround->collType = CollGround;

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

/*
Update world status for this frame
dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	CheckCameraAndWorldMap();

	vector<LPGAMEOBJECT> coObjects;	
	coObjects.push_back(baseGround);		
	grid->CalcColliableObjs(camera, coObjects);

	aladdin->HandleKeyBoard();
	
	aladdin->Update(dt);
	
	aladdin->nx = 0;
	aladdin->ny = 0;
	for (int i = 0; i < coObjects.size(); i++)
	{
		Collision::CheckCollision(aladdin, coObjects[i]);
		coObjects[i]->Update(dt);
	}
	for (int i = 0; i < Aladdin::GetInstance()->GetListApples()->size(); i++)
		Aladdin::GetInstance()->GetListApples()->at(i)->ProcessInput();
	for (int i = 0; i < aladdin->GetListApples()->size(); i++)
	{
		Collision::CheckCollision(aladdin->GetListApples()->at(i), coObjects[i]);		
	}
	Collision::CheckCollision(aladdin, baseGround);	
	
	//aladdin->CheckCollision(&coObjects);
}

/*
Render a frame: ở đây là vẽ ảnh hoặc animation
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 0.0f, 0);

	if (d3ddv->BeginScene())
	{
		vector<LPGAMEOBJECT> coObjects;		
		coObjects.push_back(baseGround);		
		grid->CalcColliableObjs(camera, coObjects);
		
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
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(0, 0, 0, 0);
}

// Tạo cửa sổ game
HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			//game->ProcessMouse();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = Game::GetInstance();
	game->Init(hWnd);	
	game->InitKeyboard();
	//game->InitMouse();

	LoadResources();

	// phóng đại game lên 2 lần
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
