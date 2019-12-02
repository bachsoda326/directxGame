#include "Peddler.h"
#include "Textures.h"

Peddler::Peddler(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 6;
	y = yDraw + 52;
	direction = true;
	collType = CollUnknown;
}

void Peddler::LoadResources()
{
	LPDIRECT3DTEXTURE9 texPeddler = Textures::GetInstance()->Get(ID_TEX_PEDDLER);

	animationStand = new Animation("Stand", XML_PEDDLER_ANIMATION_PATH, texPeddler, 100);
	animationCreate = new Animation("Create", XML_PEDDLER_ANIMATION_PATH, texPeddler, 100);

	currentAnimation = animationStand;	
}

void Peddler::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	/*x += dx;
	y += dy;*/
}

void Peddler::Render()
{
	if (true)
	{
		// // Vector trans giúp dời ảnh theo camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, trans);
	}
	else
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0));

	//RenderBoundingBox();
}

void Peddler::SetAnimation(PeddlerAnimations ani)
{
	switch (ani)
	{
	case ANI_STAND:
	{
		//reset frame when press event
		currentAnimation = animationStand;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_CREATE:
	{
		currentAnimation = animationCreate;
		//currentAnimation->ResetFrame();
		break;
	}
	}
}

Peddler::~Peddler()
{
}
