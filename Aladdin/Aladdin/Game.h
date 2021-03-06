﻿#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Constants.h"
#include <algorithm>
#include "GameSound.h"
#include <string>

class Game
{
	static Game * __instance;
	HWND hWnd;									// ưindow handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// sprite device giúp vẽ ảnh 2D lên màn hình 

	LPDIRECTINPUT8       di;					// the DirectInput object         
	LPDIRECTINPUTDEVICE8 didv_keyboard;			// the keyboard device 
	LPDIRECTINPUTDEVICE8 didv_mouse;			// the mouse device 

	
	DIMOUSESTATE mouseStates;					// DirectInput mouse state buffer

	//DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];	// Buffered keyboard data
	DIDEVICEOBJECTDATA mouseEvents[MOUSE_BUFFER_SIZE];		// Buffered mouse data	

	float cam_x = 0.0f;
	float cam_y = 0.0f;

public:
	// Khởi tạo bàn phím
	void InitKeyboard();
	// Khởi tạo chuột
	void InitMouse();
	// Khởi tạo DirectX, tạo các Direct3D devices cho việc render trong cửa sổ game, device cho việc vẽ lên màn hình
	void Init(HWND hWnd);	
	// Gọi xử lý bàn phím	
	void ProcessKeyboard();
	// Gọi xử lý chuột
	void ProcessMouse();
	// Phím được nhấn xuống
	int KeyDown(int key);
	// Chuột được nhấn xuống
	int IsMouseDown(int MouseCode);
	
	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }

	static Game * GetInstance();

	~Game();
};


