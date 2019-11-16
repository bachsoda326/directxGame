#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "tinyxml2.h"

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	float left;
	float top;
	float width;
	float height;
	float oX;
	float oY;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, float left, float top, float width, float height, float oX, float oY, LPDIRECT3DTEXTURE9 tex);

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void Draw(float x, float y, D3DXVECTOR2 transform);
	void Draw(float x, float y, float &xDraw, float &yDraw, bool direction, D3DXVECTOR2 transform, int alpha = 255);
};

typedef CSprite * LPSPRITE;

/*
Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, float left, float top, float width, float height, float oX, float oY, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	LPSPRITE &operator[](int id) { return sprites[id]; }

	static CSprites * GetInstance();
};

/*
Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int firstFrame, lastFrame;
	int currentFrame;
	bool isActionDone;
	vector<LPANIMATION_FRAME> frames;
public:	
	//// test frames public
	//int firstFrame, lastFrame;
	//vector<LPANIMATION_FRAME> frames;
	CAnimation(char* animationName, char* xmlPath, LPDIRECT3DTEXTURE9 texture, int defaultTime);
	CAnimation(int defaultTime) 
	{
		this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1;
		firstFrame = 0; lastFrame = 0;
	}

	void LoadXML(char * animationName, char* xmlPath, LPDIRECT3DTEXTURE9 texture);
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, float &xDraw, float &yDraw, bool direction, D3DXVECTOR2 transform, int alpha = 255);
	void ResetFrame();
	void SetFrame(int firstFrame, int lastFrame);
	void SetCurrentFrame(int i);
	int GetCurrentFrame();
	int GetFirstFrame();
	int GetLastFrame();
	void SetCurrentSize(float &width, float &height);
	bool isActionFinish();
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};