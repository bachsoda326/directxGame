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
#include "Constants.h"

//#define WINDOW_CLASS_NAME L"BallWindow"
//#define MAIN_WINDOW_TITLE L"Ball"
//
//#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
//#define SCREEN_WIDTH 320
//#define SCREEN_HEIGHT 240
//
//#define MAX_FRAME_RATE 120
//
//#define ID_TEX_BALL 0
//#define ID_TEX_LEFTBAR 10
//#define ID_TEX_RIGHTBAR 20
//#define ID_TEX_NUMBER 30

CGame *game;

CBall *ball;
CBar *leftBar, *rightBar, *numBar;
CNumber *leftNum, *rightNum;

LPDIRECT3DTEXTURE9 texCenterBar;

vector<LPGAMEOBJECT> objects;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void OnKeyDown(int KeyCode, int KeyState);
	virtual void OnKeyUp(int KeyCode);
	virtual void OnMouseDown(int mouseCode, int mouseState);
};

CSampleKeyHander * keyHandler;

// handle keyboard
void CSampleKeyHander::OnKeyDown(int KeyCode, int KeyState)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (KeyCode == DIK_SPACE && (KeyState && 0x80))
	{
		ball->SetPosition(150, 90);
		ball->SetSpeed();
	}

	if (KeyCode == DIK_W && (KeyState & 0x80))
	{
		if (leftBar->y <= 1)
			leftBar->SetState(BAR_STATE_STAND);
		else
			leftBar->SetState(BAR_STATE_UP);
	}
	else if (KeyCode == DIK_S && (KeyState & 0x80))
	{
		if (leftBar->y >= 150)
			leftBar->SetState(BAR_STATE_STAND);
		else
			leftBar->SetState(BAR_STATE_DOWN);
	}
	else
		leftBar->SetState(BAR_STATE_STAND);

	// test rightBar with keyboard
	if (KeyCode == DIK_UP && (KeyState & 0x80))
	{
		if (rightBar->y <= 1)
			rightBar->SetState(BAR_STATE_STAND);
		else
			rightBar->SetState(BAR_STATE_UP);
	}
	else if (KeyCode == DIK_DOWN && (KeyState & 0x80))
	{
		if (rightBar->y >= 150)
			rightBar->SetState(BAR_STATE_STAND);
		else
			rightBar->SetState(BAR_STATE_DOWN);
	}
	else
		rightBar->SetState(BAR_STATE_STAND);
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

// handle mouse
void CSampleKeyHander::OnMouseDown(int mouseCode, int mouseState)
{
	if (mouseCode == DIMOFS_BUTTON0 && (mouseState & 0x80))
	{
		if (rightBar->y <= 1)
			rightBar->SetState(BAR_STATE_STAND);
		else
			rightBar->SetState(BAR_STATE_UP);
	}
	else if (mouseCode == DIMOFS_BUTTON1 && (mouseState & 0x80))
	{
		if (rightBar->y >= 150)
			rightBar->SetState(BAR_STATE_STAND);
		else
			rightBar->SetState(BAR_STATE_DOWN);
	}
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
In this example: load textures, sprites, animations and s.t object

TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	// create texture from path and add to "textures"
	textures->Add(ID_TEX_BALL, L"textures\\ball.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_LEFTBAR, L"textures\\bar.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_RIGHTBAR, L"textures\\bar.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_NUMBER, L"textures\\numbers.png", D3DCOLOR_XRGB(153, 217, 234));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	// small bar between numbers
	texCenterBar = textures->Get(ID_TEX_LEFTBAR);

	// get object texture and add to "sprites" with RECT
	LPDIRECT3DTEXTURE9 texBall = textures->Get(ID_TEX_BALL);	
	sprites->Add(10001, 0, 0, 16, 16, texBall);

	LPDIRECT3DTEXTURE9 texLeftBar = textures->Get(ID_TEX_LEFTBAR);
	sprites->Add(20001, 0, 0, 10, 45, texLeftBar);

	LPDIRECT3DTEXTURE9 texRightBar = textures->Get(ID_TEX_RIGHTBAR);
	sprites->Add(30001, 0, 0, 10, 45, texRightBar);

	LPDIRECT3DTEXTURE9 texNumber = textures->Get(ID_TEX_NUMBER);
	sprites->Add(40000, 14, 8, 28, 27, texNumber);		// width: 14-15 || distance: 15
	sprites->Add(40001, 29, 8, 44, 27, texNumber);
	sprites->Add(40002, 44, 8, 58, 27, texNumber);
	sprites->Add(40003, 59, 8, 74, 27, texNumber);
	sprites->Add(40004, 74, 8, 90, 27, texNumber);
	sprites->Add(40005, 93, 8, 108, 27, texNumber);
	sprites->Add(40006, 111, 8, 126, 27, texNumber);
	sprites->Add(40007, 129, 8, 144, 27, texNumber);
	sprites->Add(40008, 147, 8, 162, 27, texNumber);
	sprites->Add(40009, 165, 8, 180, 27, texNumber);

	LPANIMATION ani;

	ani = new CAnimation(100);		
	ani->Add(40000);
	animations->Add(300, ani);		// number 0 animation id: 300
	ani = new CAnimation(100);		
	ani->Add(40001);
	animations->Add(301, ani);
	ani = new CAnimation(100);		
	ani->Add(40002);
	animations->Add(302, ani);
	ani = new CAnimation(100);		
	ani->Add(40003);
	animations->Add(303, ani);
	ani = new CAnimation(100);		
	ani->Add(40004);
	animations->Add(304, ani);
	ani = new CAnimation(100);		
	ani->Add(40005);
	animations->Add(305, ani);
	ani = new CAnimation(100);		
	ani->Add(40006);
	animations->Add(306, ani);
	ani = new CAnimation(100);		
	ani->Add(40007);
	animations->Add(307, ani);
	ani = new CAnimation(100);		
	ani->Add(40008);
	animations->Add(308, ani);
	ani = new CAnimation(100);		
	ani->Add(40009);
	animations->Add(309, ani);		// number 9 animation id: 309

	ani = new CAnimation(100);		
	ani->Add(10001);
	animations->Add(400, ani);		// ball animation id: 400

	ani = new CAnimation(100);		
	ani->Add(20001);
	animations->Add(501, ani);		// leftbar animation id: 501

	ani = new CAnimation(100);		
	ani->Add(30001);	
	animations->Add(601, ani);		// rightbar animation id: 601

	leftNum = new CNumber();
	leftNum->AddAnimation(300);
	leftNum->AddAnimation(301);
	leftNum->AddAnimation(302);
	leftNum->AddAnimation(303);
	leftNum->AddAnimation(304);
	leftNum->AddAnimation(305);
	leftNum->AddAnimation(306);
	leftNum->AddAnimation(307);
	leftNum->AddAnimation(308);
	leftNum->AddAnimation(309);
	leftNum->SetPosition(130, 10);

	rightNum = new CNumber();
	rightNum->AddAnimation(300);
	rightNum->AddAnimation(301);
	rightNum->AddAnimation(302);
	rightNum->AddAnimation(303);
	rightNum->AddAnimation(304);
	rightNum->AddAnimation(305);
	rightNum->AddAnimation(306);
	rightNum->AddAnimation(307);
	rightNum->AddAnimation(308);
	rightNum->AddAnimation(309);
	rightNum->SetPosition(170, 10);

	ball = new CBall();
	ball->AddAnimation(400);
	ball->SetPosition(150, 90);
	objects.push_back(ball);	

	leftBar = new CBar();
	leftBar->AddAnimation(501);
	leftBar->SetPosition(10, 90);
	objects.push_back(leftBar);

	rightBar = new CBar();
	rightBar->AddAnimation(601);
	rightBar->SetPosition(285, 90);
	objects.push_back(rightBar);

	numBar = new CBar();
	numBar->AddAnimation(501);
	numBar->SetPosition(150, 10);
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

	for (int i = 1; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	ball->Update(dt, leftNum, rightNum, &coObjects);

	/*ball->Update(dt, &coObjects);
	leftBar->Update(dt, &coObjects);
	rightBar->Update(dt, &coObjects);*/

	// Update camera to follow ball
	//float cx, cy;
	//ball->GetPosition(cx, cy);

	//cx -= SCREEN_WIDTH / 2;
	//cy -= SCREEN_HEIGHT / 2;

	//CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
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

		// render numbers
		leftNum->Render();
		rightNum->Render();				
		
		// handling centerBar between two numbers: scale down the centerBar img
		D3DXMATRIX deScale, mScale;
		D3DXMatrixScaling(&deScale, 1.0f, 1.0f, .0f);		
		D3DXVECTOR2 scalingScenter = D3DXVECTOR2(152 + 10/2, 10);	// position.x + width/2, position.y
		D3DXVECTOR2 inScale = D3DXVECTOR2(0.3, 0.4);				// scale: 0.3x, 0.4y	
		D3DXMatrixTransformation2D(&mScale, &scalingScenter, NULL, &inScale, NULL, NULL, NULL);		

		D3DXVECTOR3 p(152, 10, 0);
		RECT r;
		r.left = 0;
		r.top = 0;
		r.right = 10;
		r.bottom = 45;
		
		// draw centerBar
		spriteHandler->SetTransform(&mScale);
		spriteHandler->Draw(texCenterBar, &r, NULL, &p, D3DCOLOR_ARGB(100, 255, 255, 255));
		spriteHandler->SetTransform(&deScale);	// set transform back no default(1, 1, 1)

		// render main objects
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