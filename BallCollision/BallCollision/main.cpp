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
#include "Ball.h"
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
//#define ID_TEX_STANDBALL 0
//#define ID_TEX_LEFTBAR 10
//#define ID_TEX_RIGHTBAR 20
//#define ID_TEX_NUMBER 30

CGame *game;

CCamera *camera;

CGrid *grid;

CBall *ball;

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
		/*ball->SetPosition(150, 90);
		ball->SetSpeed();*/
	}

	if (KeyCode == DIK_UP && (KeyState & 0x80))
	{
		ball->SetSpeed(0, -BALL_SPEED);
	}
	else if (KeyCode == DIK_DOWN && (KeyState & 0x80))
	{
		ball->SetSpeed(0, BALL_SPEED);
	}
	else if (KeyCode == DIK_LEFT && (KeyState & 0x80))
	{
		ball->SetSpeed(-BALL_SPEED, 0);
	}
	else if (KeyCode == DIK_RIGHT && (KeyState & 0x80))
	{
		ball->SetSpeed(BALL_SPEED, 0);
	}
	else
		ball->SetSpeed(0, 0);

	// test rightBar with keyboard
	/*if (KeyCode == DIK_UP && (KeyState & 0x80))
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
		rightBar->SetState(BAR_STATE_STAND);*/
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
		/*if (rightBar->y <= 1)
			rightBar->SetState(BAR_STATE_STAND);
		else
			rightBar->SetState(BAR_STATE_UP);*/
	}
	else if (mouseCode == DIMOFS_BUTTON1 && (mouseState & 0x80))
	{
		/*if (rightBar->y >= 150)
			rightBar->SetState(BAR_STATE_STAND);
		else
			rightBar->SetState(BAR_STATE_DOWN);*/
	}
	/*else
		rightBar->SetState(BAR_STATE_STAND);*/
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

void CheckCameraAndWorldMap()
{
	// test Camera move when Mario is not on center screen
	//mCamera->SetPosition(mPlayer->GetPosition() + D3DXVECTOR3(100,0,0));
	camera->SetPosition(ball->GetPosition());

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

	// create texture from path and add to "textures"
	textures->Add(ID_TEX_BALL, L"textures\\blackBall.png", NULL);
	textures->Add(ID_TEX_STANDBALL, L"textures\\ball.png", D3DCOLOR_XRGB(255, 255, 255));	

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	// get object texture and add to "sprites" with RECT
	LPDIRECT3DTEXTURE9 texBall = textures->Get(ID_TEX_BALL);
	sprites->Add(10000, 0, 0, 16, 16, texBall);

	LPDIRECT3DTEXTURE9 texStandBall = textures->Get(ID_TEX_STANDBALL);	
	sprites->Add(10001, 0, 0, 16, 16, texStandBall);
		
	LPANIMATION ani;

	ani = new CAnimation(10000);
	ani->Add(10000);
	animations->Add(200, ani);		// ball animation id: 200	
	
	ani = new CAnimation(10000);		
	ani->Add(10001);
	animations->Add(400, ani);		// standBall animation id: 400	

	camera = new CCamera(SCREEN_WIDTH, SCREEN_HEIGHT);

	grid = new CGrid(MAP_WIDTH, MAP_HEIGHT, 150);

	ball = new CBall();
	ball->AddAnimation(200);
	ball->SetPosition(20, 20);
	ball->SetCamera(camera);
	grid->AddBall(ball);
	objects.push_back(ball);
	
	srand(time(NULL));
	for (int i = 0; i < 60; i++)
	{
		CBall *standBall = new CBall();
		standBall->AddAnimation(400);
		standBall->SetRanDomPosition();
		standBall->SetCamera(camera);
		grid->AddBall(standBall);
		objects.push_back(standBall);
	}

	CBall *edgeBall1 = new CBall();
	edgeBall1->AddAnimation(400);
	edgeBall1->SetPosition(0, 0);
	edgeBall1->SetCamera(camera);
	grid->AddBall(edgeBall1);
	objects.push_back(edgeBall1);

	CBall *edgeBall2 = new CBall();
	edgeBall2->AddAnimation(400);
	edgeBall2->SetPosition(MAP_WIDTH - 16, 0);
	edgeBall2->SetCamera(camera);
	grid->AddBall(edgeBall2);
	objects.push_back(edgeBall2);

	CBall *edgeBall3 = new CBall();
	edgeBall3->AddAnimation(400);
	edgeBall3->SetPosition(0, MAP_HEIGHT - 16);
	edgeBall3->SetCamera(camera);
	grid->AddBall(edgeBall3);
	objects.push_back(edgeBall3);

	CBall *edgeBall4 = new CBall();
	edgeBall4->AddAnimation(400);
	edgeBall4->SetPosition(MAP_WIDTH - 16, MAP_HEIGHT - 16);
	edgeBall4->SetCamera(camera);
	grid->AddBall(edgeBall4);
	objects.push_back(edgeBall4);
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
	/*for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}*/

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
	}

	// Make camera following the main ball
	CheckCameraAndWorldMap();

	grid->CalcColliableObjs(camera, coObjects);

	ball->CheckCollision(&coObjects);
		
	// Update camera to follow ball
	/*float cx, cy;
	ball->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;

	CGame::GetInstance()->SetCamPos(cx, cy);*/
}

/*
Render a frame
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