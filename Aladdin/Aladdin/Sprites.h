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
	// độ dời oX, oY theo trục ox, oy để thay đổi vị trí vẽ (để cân xứng giữa các frame hình của animation)
	float oX;
	float oY;
	// texture lớn
	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, float left, float top, float width, float height, float oX, float oY, LPDIRECT3DTEXTURE9 tex);

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	// Vẽ xài khi vẽ ảnh
	void Draw(float x, float y, D3DXVECTOR2 transform);
	// Vẽ xài khi vẽ animation
	void Draw(float x, float y, float &xDraw, float &yDraw, bool direction, D3DXVECTOR2 transform, int alpha = 255);
};

typedef CSprite * LPSPRITE;

/*
Quản lý sprite database
*/
class CSprites
{
	static CSprites * __instance;
	// kiểu như listSprites
	unordered_map<int, LPSPRITE> sprites;

public:
	// Thêm sprite vào instance"sprites"
	void Add(int id, float left, float top, float width, float height, float oX, float oY, LPDIRECT3DTEXTURE9 tex);
	// Get sprite theo id trong instance"sprites"
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
	// t.gian chuyển giữa các sprite
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
	// listFrames; mỗi frame gồm 1 sprite và time (t.gian chuyển frame)
	vector<LPANIMATION_FRAME> frames;
public:		
	CAnimation(char* animationName, char* xmlPath, LPDIRECT3DTEXTURE9 texture, int defaultTime);
	CAnimation(int defaultTime) 
	{
		this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1;
		firstFrame = 0; lastFrame = 0;
	}

	// Đọc file animation.xml
	void LoadXML(char * animationName, char* xmlPath, LPDIRECT3DTEXTURE9 texture);
	// Add sprite vào listFrames của animation
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, float &xDraw, float &yDraw, bool direction, D3DXVECTOR2 transform, int alpha = 255);
	void ResetFrame();
	void SetFrame(int firstFrame, int lastFrame);
	void SetCurrentFrame(int i);
	int GetCurrentFrame();
	int GetFirstFrame();
	int GetLastFrame();
	// Set size của obj (do sự thay đổi size khi vẽ từng sprite khác nhau)
	void SetCurrentSize(float &width, float &height);
	bool isActionFinish();
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;
	// kiểu như listAnimations
	unordered_map<int, LPANIMATION> animations;

public:
	// Thêm animation vào instance"animations"
	void Add(int id, LPANIMATION ani);
	// Get animation theo id trong instance"animations"
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};