#pragma once

#define WINDOW_CLASS_NAME L"BallWindow"
#define MAIN_WINDOW_TITLE L"Ball"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define MAX_FRAME_RATE 120			// FPS

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
#define MOUSE_BUFFER_SIZE 100

// id for storing textures in: unodered_map<int id, LPDIRECT3DTEXTURE9 texture> textures
#define ID_TEX_BALL 0				
#define ID_TEX_LEFTBAR 10
#define ID_TEX_RIGHTBAR 20
#define ID_TEX_NUMBER 30

#define BALL_BBOX_WIDTH  16			// ball's width
#define BALL_BBOX_HEIGHT 16			// ball's height
#define BALL_SPEED 0.2f

#define BAR_BBOX_WIDTH  10			// bar's width
#define BAR_BBOX_HEIGHT 45			// bar's height
#define BAR_STATE_STAND 0
#define BAR_STATE_UP 100
#define BAR_STATE_DOWN 200
#define BAR_SPEED 0.15f

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
