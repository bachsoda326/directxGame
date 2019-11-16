#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Constants.h"

//#define DIRECTINPUT_VERSION 0x0800
//
//#define KEYBOARD_BUFFER_SIZE 1024
//#define MOUSE_BUFFER_SIZE 100
/*
Abstract class to define keyboard event handlers
*/

class CGame
{
	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;				// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv_keyboard;		// The keyboard device 
	LPDIRECTINPUTDEVICE8 didv_mouse;		// The mouse device 

	
	DIMOUSESTATE mouseStates;		// DirectInput mouse state buffer

	//DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	DIDEVICEOBJECTDATA mouseEvents[MOUSE_BUFFER_SIZE];		// Buffered mouse data	

	float cam_x = 0.0f;
	float cam_y = 0.0f;

public:
	void InitKeyboard();
	void InitMouse();
	void Init(HWND hWnd);	
		
	void ProcessKeyboard();
	void ProcessMouse();
	int KeyDown(int key);
	int IsMouseDown(int MouseCode);

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float &t,
		float &nx,
		float &ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }

	static CGame * GetInstance();

	~CGame();
};


