/* =============================================================
INTRODUCTION TO GAME PROGRAMMING SE102

SAMPLE 04 - COLLISION

This sample illustrates how to:

1/ Implement SweptAABB algorithm between moving objects
2/ Implement a simple (yet effective) collision frame work

Key functions:
CGame::SweptAABB
CGameObject::SweptAABBEx
CGameObject::CalcPotentialCollisions
CGameObject::FilterCollision

CGameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Grid.h"
#include "Aladdin.h"
#include "Map.h"
#include "Constants.h"

CGame *game;
CCamera *camera = CCamera::GetInstance();
CGrid *grid;
CMap *map, *map1;
CAladdin *aladdin = CAladdin::GetInstance();

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

	if (camera->GetBound().right > MAP_WIDTH)
	{
		//luc nay cham goc ben phai cua the gioi thuc
		camera->SetPosition(MAP_WIDTH - camera->GetWidth() / 2,
			camera->GetPosition().y);
	}

	if (camera->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		camera->SetPosition(camera->GetPosition().x, camera->GetHeight() / 2);
	}

	if (camera->GetBound().bottom > MAP_HEIGHT)
	{
		//luc nay cham day cua the gioi thuc
		camera->SetPosition(camera->GetPosition().x,
			MAP_HEIGHT - camera->GetHeight() / 2);
	}
}

/*
Load all game resources
In this example: load textures, sprites, animations and s.t object

TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	// tạo texture lớn từ đường dẫn và add vào instance"textures"
	textures->Add(1, L"textures\\map.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(2, L"textures\\map1.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ALADDIN, L"textures\\Aladdin.png", D3DCOLOR_XRGB(255, 0, 255));	

	CSprites * sprites = CSprites::GetInstance();

	// lấy texture lớn từ instance"textures"
	LPDIRECT3DTEXTURE9 texMap = textures->Get(1);
	LPDIRECT3DTEXTURE9 texMap1 = textures->Get(2);
	// tạo sprite từ texture lớn thông qua RECT và add vào instance"sprites"
	sprites->Add(10069, 0, 0, 2271, 1139, 0, 0, texMap);
	sprites->Add(20069, 0, 0, 2271, 1139, 0, 0, texMap1);
	
	grid = new CGrid(MAP_WIDTH, MAP_HEIGHT, 150);

	map = new CMap(10069);
	map->AddAnimation(10);
	map->SetPosition(0, 0);
	//map->SetCamera(camera);
	objects.push_back(map);	

	//aladdin = new CAladdin();
	aladdin->LoadResources();
	aladdin->SetPosition(115, 1000);
	//aladdin->SetPosition(115, 1120);
	//aladdin->SetCamera(camera);
	//grid->AddObjToCell(aladdin);
	objects.push_back(aladdin);	

	map1 = new CMap(20069);
	map1->AddAnimation(20);
	map1->SetPosition(0, 0);
	//map1->SetCamera(camera);
	objects.push_back(map1);
}

/*
Update world status for this frame
dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;

	aladdin->HandleKeyBoard();

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
	}	
		
	CheckCameraAndWorldMap();

	//grid->CalcColliableObjs(camera, coObjects);

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
		// Clear back buffer with a color
		//d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		// render main objects
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

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

	game = CGame::GetInstance();
	game->Init(hWnd);	
	game->InitKeyboard();
	//game->InitMouse();

	LoadResources();

	// phóng đại game lên 2 lần
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}