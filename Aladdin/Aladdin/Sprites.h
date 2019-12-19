#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "tinyxml2.h"

using namespace std;

class Sprite
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
	Sprite(int id, float left, float top, float width, float height, float oX, float oY, LPDIRECT3DTEXTURE9 tex);

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	// Vẽ xài khi vẽ ảnh test
	void DrawTest(float x, float y, D3DXVECTOR2 transform, int alpha = 255);
	// Vẽ xài khi vẽ ảnh
	void Draw(float x, float y, D3DXVECTOR2 transform);
	// Vẽ xài khi vẽ animation
	void Draw(float x, float y, float &xDraw, float &yDraw, float &w, float &h, bool direction, D3DXVECTOR2 transform, int alpha = 255);
};

typedef Sprite * LPSPRITE;

/*
Quản lý sprite database
*/
class Sprites
{
	static Sprites * __instance;
	// kiểu như listSprites
	unordered_map<int, LPSPRITE> sprites;

public:
	// Thêm sprite vào instance"sprites"
	void Add(int id, float left, float top, float width, float height, float oX, float oY, LPDIRECT3DTEXTURE9 tex);
	// Get sprite theo id trong instance"sprites"
	LPSPRITE Get(int id);
	LPSPRITE &operator[](int id) { return sprites[id]; }

	static Sprites * GetInstance();
};

/*
Sprite animation
*/
class AnimationFrame
{
	LPSPRITE sprite;
	// t.gian chuyển giữa các sprite
	DWORD time;

public:
	AnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef AnimationFrame *LPANIMATION_FRAME;

class Animation
{
	// t.gian của frame animation trước đó
	DWORD lastFrameTime;
	// t.gian mặc định chuyển frame animation
	int defaultTime;
	// frame đầu của animation
	int firstFrame;
	// frame cuối của animation
	int lastFrame;
	// frame hiện tại của animation
	int currentFrame;
	// true: animation đã xong | false: animation chưa xong
	bool isActionDone;
	// listFrames; mỗi frame gồm 1 sprite và time (t.gian chuyển frame)
	vector<LPANIMATION_FRAME> frames;
public:		
	Animation(char* animationName, char* xmlPath, LPDIRECT3DTEXTURE9 texture, int defaultTime);
	Animation(int defaultTime) 
	{
		this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1;
		firstFrame = 0; lastFrame = 0;
	}

	// Đọc file animation.xml
	void LoadXML(char * animationName, char* xmlPath, LPDIRECT3DTEXTURE9 texture);
	// Add sprite vào listFrames của animation
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, float &xDraw, float &yDraw, float &w, float &h, bool direction, D3DXVECTOR2 transform, int isBlink = 0);
	// reset frame animation về đầu
	void ResetFrame();
	// set firstFrame đến lastFrame
	void SetFrame(int firstFrame, int lastFrame);
	void SetCurrentFrame(int i);
	int GetCurrentFrame();
	int GetFirstFrame();
	int GetLastFrame();
	bool isActionFinish();
};

typedef Animation *LPANIMATION;

class Animations
{
	static Animations * __instance;
	// kiểu như listAnimations
	unordered_map<int, LPANIMATION> animations;

public:
	// Thêm animation vào instance"animations"
	void Add(int id, LPANIMATION ani);
	// Get animation theo id trong instance"animations"
	LPANIMATION Get(int id);

	static Animations * GetInstance();
};