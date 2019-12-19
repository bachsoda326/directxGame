#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Camera.h"
#include "GameObject.h"
#include "Aladdin.h"
#include "BloodBar.h"
#include "AladdinFace.h"
#include "Apple.h"
#include "Ruby.h"

class Scene
{
public:
	D3DXFONT_DESC desc;
	// các font tương ứng số táo, ruby, mạng, điểm
	LPD3DXFONT numApples, numRubies, numLifes, score;

	// thanh máu của Aladdin
	BloodBar *bloodBar;
	// số mạng của Aladdin
	AladdinFace *face;
	Apple *aladdinApple;
	Ruby *aladdinRuby;

public:
	Scene();

	virtual void LoadResources();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	// Cập nhật vị trí camera khi đụng biên map và khi Aladdin di chuyển
	void UpdateCamera(int mapWidth, int mapHeight);
	void LoadFont();
	void DrawFont(LPD3DXFONT font, float x, float y, float width, float height, int value);
	// Vẽ các chỉ số của Aladdin
	void DrawFonts();

	~Scene();
};

