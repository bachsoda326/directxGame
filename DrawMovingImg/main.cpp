#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"DrawMovingImg"

#define BRICK_TEXTURE_PATH L"brick.png"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 0, 0)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

CGame *game;
CTextures * textures;

//LPDIRECT3DSURFACE9 surface = NULL;

int x = 0;
int y = 0;

float vx, vy;

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

/*
Load all game resources. In this example, only load brick image
*/
void LoadResources()
{
	textures = CTextures::GetInstance();

	textures->Add(1, L"brick.png", D3DCOLOR_XRGB(255, 255, 255));

	//LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	//int result =
	//	d3ddv->CreateOffscreenPlainSurface(
	//		100,
	//		100,				// height
	//		D3DFMT_X8R8G8B8,		// format
	//		D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
	//		&surface,
	//		NULL);

	//result = D3DXLoadSurfaceFromFile(
	//	surface, 		// surface
	//	NULL,			// destination palette	
	//	NULL,			// destination rectangle 
	//	BRICK_TEXTURE_PATH,
	//	NULL,			// source rectangle
	//	D3DX_DEFAULT, 		// filter image
	//	0,			// transparency (0 = none)
	//	NULL);			// reserved
}

/*
Update world status for this frame
dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	if (x >= 220)
	{
		vx = 0;
		vy = 0.1f;
		x = 220;
		y += vy*dt;
	}

	if (x <= 50)
	{
		vx = 0;
		vy = -0.1f;
		x = 50;
		y += vy*dt;
	}

	if (y <= 50)
	{	
		vy = 0;
		vx = 0.1f;
		y = 50;
		x += vx*dt;		
	}

	if (y >= 120)
	{
		vy = 0;
		vx = -0.1f;
		y = 120;
		x += vx*dt;		
	}
}

/*
Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 backBuffer = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear screen (back buffer) with a color
		d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		
		D3DXVECTOR3 p((float)x, (float)y, 0);
		//spriteHandler->Draw(texBrick, NULL, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
		game->Draw(x, y, textures->Get(1));

		//RECT rect;

		//rect.left = rand() % (SCREEN_WIDTH / 2);
		//rect.top = rand() % (SCREEN_HEIGHT / 2);
		//rect.right = rect.left + rand() % (SCREEN_WIDTH / 2);
		//rect.bottom = rect.top + rand() % (SCREEN_HEIGHT / 2);
		//d3ddv->StretchRect(
		//	surface,			// from 
		//	NULL,				// which portion?
		//	backBuffer,			// to 
		//	&rect,				// which portion?
		//	D3DTEXF_NONE);

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

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

	LoadResources();
	Run();

	return 0;
}