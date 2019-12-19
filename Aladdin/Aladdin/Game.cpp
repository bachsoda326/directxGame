#include "Game.h"
#include "debug.h"

Game * Game::__instance = NULL;

/*
Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
rendering 2D images
- hInst: Application instance handle
- hWnd: Application window handle
*/

void Game::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	//RECT r;
	//GetClientRect(hWnd, &r);	// retrieve Window width & height 

	//d3dpp.BackBufferHeight = r.bottom + 1;
	//d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString("[ERROR] CreateDevice failed\n");
		return;
	}

	//d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString("[INFO] InitGame done;\n");

	GameSound::initialize(hWnd);
}

BYTE  keys[256];			// DirectInput keyboard state buffer (keyBoard input)

void Game::InitKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		DebugOut("[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv_keyboard, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		DebugOut("[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv_keyboard->SetDataFormat(&c_dfDIKeyboard);

	hr = didv_keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);	

	hr = didv_keyboard->Acquire();
	if (hr != DI_OK)
	{
		DebugOut("[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut("[INFO] Keyboard has been initialized successfully\n");
}

void Game::ProcessKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = didv_keyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv_keyboard->Acquire();
			if (h == DI_OK)
			{
				DebugOut("[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}
}

void Game::InitMouse()
{
	HRESULT
		hr = DirectInput8Create
		(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		DebugOut("[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysMouse, &didv_mouse, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		DebugOut("[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv_mouse->SetDataFormat(&c_dfDIMouse);

	hr = didv_mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv_mouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv_mouse->Acquire();
	if (hr != DI_OK)
	{
		DebugOut("[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut("[INFO] Mouse has been initialized successfully\n");
}

void Game::ProcessMouse()
{
	HRESULT hr;

	// collect all key states first
	hr = didv_mouse->GetDeviceState(sizeof(mouseStates), (LPVOID)&mouseStates);
	if (FAILED(hr))
	{
		// If the Mouse lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv_mouse->Acquire();
			if (h == DI_OK)
			{
				DebugOut("[INFO] Mouse re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	// collect all buffered events
	DWORD dwElements = MOUSE_BUFFER_SIZE;
	hr = didv_mouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mouseEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int mouseCode = mouseEvents[i].dwOfs;
		int mouseState = mouseEvents[i].dwData;
		
	}

	//keyHandler->MouseState(&mouseStates);
}

int Game::KeyDown(int key)
{
	return (keys[key] & 0x80);
}

int Game::IsMouseDown(int MouseCode)
{
	return (mouseStates.rgbButtons[MouseCode] & 0x80) > 0;
}

Game::~Game()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

Game *Game::GetInstance()
{
	if (__instance == NULL) __instance = new Game();
	return __instance;
}
