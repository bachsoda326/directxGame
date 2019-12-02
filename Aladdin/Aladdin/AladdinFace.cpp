#include "AladdinFace.h"

AladdinFace::AladdinFace()
{
}

void AladdinFace::LoadResources()
{
	x = xDraw + 11;
	y = yDraw + 12;

	Item::LoadResources();

	LPDIRECT3DTEXTURE9 texItems = Textures::GetInstance()->Get(ID_TEX_ITEM);

	animationDefault = new Animation("Animation", XML_ALADDINFACE_ANIMATION_PATH, texItems, 100);

	currentAnimation = animationDefault;
}

void AladdinFace::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void AladdinFace::Render()
{
	currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0));
}

void AladdinFace::ProcessInput()
{
}

AladdinFace::~AladdinFace()
{
}
