#pragma once

#define WINDOW_CLASS_NAME L"BallWindow"
#define MAIN_WINDOW_TITLE L"Ball"
#define MAX_FRAME_RATE 120		// FPS

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define MAP_WIDTH 1280
#define MAP_HEIGHT 960
#define RANDOM_WIDTH 1250
#define RANDOM_HEIGHT 930		

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
#define MOUSE_BUFFER_SIZE 100

// id for storing textures in: unodered_map<int id, LPDIRECT3DTEXTURE9 texture> textures
#define ID_TEX_BALL 0
#define ID_TEX_STANDBALL 10

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

#define BALL_BBOX_WIDTH  16
#define BALL_BBOX_HEIGHT 16
#define BALL_SPEED 0.2f
