#include "Bat.h"
#include "Textures.h"

Bat::Bat(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 3;
	y = yDraw + 16;
	isDead = false;
	direction = true;
	collType = CollEnemy;
	objType = OBJBat;
}

void Bat::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBat = Textures::GetInstance()->Get(ID_TEX_BAT);

	animationStand = new Animation("Stand", XML_BAT_ANIMATION_PATH, texBat, 100);
	animationAttack = new Animation("Attack", XML_BAT_ANIMATION_PATH, texBat, 100);
	animationDieByApple = new Animation("DieByApple", XML_BAT_ANIMATION_PATH, texBat, 100);
	animationDie = new Animation("Animation", XML_ENEMYDEAD_ANIMATION_PATH, texBat, 100);

	currentAnimation = animationStand;
	animationStand->SetFrame(0, 0);
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	/*x += dx;
	y += dy;*/
}

void Bat::SetAnimation(BatAnimations ani)
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
	case ANI_ATTACK:
	{
		currentAnimation = animationAttack;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_DIE_BY_APPLE:
	{
		currentAnimation = animationDieByApple;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_DIE:
	{
		currentAnimation = animationDie;
		//currentAnimation->ResetFrame();
		break;
	}
	}
}

Bat::~Bat()
{
}
