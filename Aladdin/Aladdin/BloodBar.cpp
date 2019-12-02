#include "BloodBar.h"

BloodBar::BloodBar()
{
}

void BloodBar::LoadResources()
{
	x = xDraw + 20;
	y = yDraw + 13;
	direction = true;	
	isDead = false;
	nx = 0.0f;
	ny = 0.0f;
	vx = 0;
	vy = 0;
	isBlink = 0;
	
	startBlink = GetTickCount();

	LPDIRECT3DTEXTURE9 texBloodBar = Textures::GetInstance()->Get(ID_TEX_BLOODBAR);

	animationDefault = new Animation("Animation", XML_BLOODBAR_ANIMATION_PATH, texBloodBar, 100);

	currentAnimation = animationDefault;
	animationDefault->SetFrame(1, 4);
}

void BloodBar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void BloodBar::Render()
{	
	if (currentAnimation->GetCurrentFrame() > 0)
	{
		x += 29;
		y -= 7;
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0));

		x -= 29;
		y += 7;
	}

	int currentIndex;
	currentIndex = currentAnimation->GetCurrentFrame();
	currentAnimation->SetCurrentFrame(0);

	//draw sprite
	currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0));
	currentAnimation->SetCurrentFrame(currentIndex);
}

void BloodBar::ProcessInput()
{
}

BloodBar::~BloodBar()
{
}
