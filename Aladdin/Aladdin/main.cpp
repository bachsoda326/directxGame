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
#include "SceneManager.h"
#include "DungeonScene.h"
#include "BossScene.h"
#include "NextScene.h"
#include "EndScene.h"
#include "OpenScene.h"
#include "debug.h"
#include "Game.h"

Game *game;

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

// Tạo texture lớn (ảnh lớn)
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
	textures->Add(ID_TEX_BOSS, TEX_BOSS_PATH, D3DCOLOR_XRGB(186, 254, 202));
	textures->Add(ID_TEX_NEXTSCENE, TEX_NEXTSCENE_PATH, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ENDSCENE, TEX_ENDSCENE_PATH, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_ABU, TEX_ABU_PATH, D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_OPENSCENE, TEX_OPENSCENE_PATH, D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_BBOX, TEX_BBOX_PATH, D3DCOLOR_XRGB(255, 255, 255));
}

/*
Update world status for this frame
dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
}

/*
Render a frame: ở đây là vẽ ảnh hoặc animation
*/
void Render()
{
	SceneManager::GetInstance()->GetCurrentScene()->Render();
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
		OutputDebugString("[ERROR] CreateWindow failed");
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
	// tạo các texture (ảnh lớn)
	LoadResources();
	// tạo vòng khởi đầu
	SceneManager::GetInstance()->ReplaceScene(new OpenScene());

	// phóng đại game lên 2 lần
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
