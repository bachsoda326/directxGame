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
#include "Ball.h"
#include "Bar.h"
#include "Number.h"

#define WINDOW_CLASS_NAME L"BallWindow"
#define MAIN_WINDOW_TITLE L"Ball"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_BALL 0
#define ID_TEX_LEFTBAR 10
#define ID_TEX_RIGHTBAR 20
#define ID_TEX_NUMBER 30

CGame *game;

CBall *ball;
CBar *leftBar, *rightBar;

vector<LPGAMEOBJECT> objects;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);	
	virtual void MouseButton(int mouseState, int mouseData);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (KeyCode == DIK_SPACE)
	{
		ball->SetPosition(150, 80);
		ball->SetSpeed();
	}		
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{	
	if (game->IsKeyDown(DIK_W))
	{
		if (leftBar->y <= 1)
			leftBar->SetState(BAR_STATE_STAND);
		else
			leftBar->SetState(BAR_STATE_UP);
	}		
	else if (game->IsKeyDown(DIK_S))
	{
		if (leftBar->y >= 150)
			leftBar->SetState(BAR_STATE_STAND);
		else
			leftBar->SetState(BAR_STATE_DOWN);
	}
	else
		leftBar->SetState(BAR_STATE_STAND);
}

void CSampleKeyHander::MouseButton(int mouseState, int mouseData)
{
	if (mouseState == DIMOFS_BUTTON0 && (mouseData & 0x80))
		rightBar->SetState(BAR_STATE_UP);		
	else if (mouseState == DIMOFS_BUTTON1 && (mouseData & 0x80))
		rightBar->SetState(BAR_STATE_DOWN);
	else
		rightBar->SetState(BAR_STATE_STAND);
}

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
Load all game resources
In this example: load textures, sprites, animations and mario object

TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	// create texture of path image
	textures->Add(ID_TEX_BALL, L"textures\\ball.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_LEFTBAR, L"textures\\bar.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_RIGHTBAR, L"textures\\bar.png", D3DCOLOR_XRGB(255, 255, 255));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	// create sprite with left, top, right(left + width), bottom(right + height)
	LPDIRECT3DTEXTURE9 texBall = textures->Get(ID_TEX_BALL);	
	sprites->Add(10001, 0, 0, 16, 16, texBall);

	LPDIRECT3DTEXTURE9 texLeftBar = textures->Get(ID_TEX_LEFTBAR);
	sprites->Add(20001, 0, 0, 10, 50, texLeftBar);

	LPDIRECT3DTEXTURE9 texRightBar = textures->Get(ID_TEX_RIGHTBAR);
	sprites->Add(30001, 0, 0, 10, 50, texRightBar);	

	LPANIMATION ani;	

	// add to animations
	ani = new CAnimation(100);		// ball
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);		// leftbar
	ani->Add(20001);
	animations->Add(501, ani);

	ani = new CAnimation(100);		// rightbar
	ani->Add(30001);	
	animations->Add(601, ani);

	ball = new CBall();
	ball->AddAnimation(400);	// add ball animations above to ball
	ball->SetPosition(150, 80);
	objects.push_back(ball);	

	leftBar = new CBar();
	leftBar->AddAnimation(501);
	leftBar->SetPosition(10, 80);
	objects.push_back(leftBar);

	rightBar = new CBar();
	rightBar->AddAnimation(601);
	rightBar->SetPosition(285, 80);
	objects.push_back(rightBar);
}

/*
Update world status for this frame
dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
}

/*
Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		
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

			game->ProcessKeyboard();
			game->ProcessMouse();

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

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);
	game->InitMouse(keyHandler);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}