#include "Peddler.h"
#include "Textures.h"

Peddler::Peddler(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 6;
	y = yDraw + 52;
	isDead = false;
	direction = true;
	collType = CollUnknown;
	objType = OBJPeddler;
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
