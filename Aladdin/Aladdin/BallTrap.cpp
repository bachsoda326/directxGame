#include "BallTrap.h"
#include "Textures.h"

BallTrap::BallTrap(float left, float top, float width, float height)
{
	x = left;
	y = top;
	isDead = false;
	direction = true;
	collType = CollUnknown;
	objType = OBJBallTrap;
}

void BallTrap::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBallTrap = Textures::GetInstance()->Get(ID_TEX_BRICK_TRAP);

	animationDefault = new Animation("Animation", XML_BALLTRAP_ANIMATION_PATH, texBallTrap, 100);

	currentAnimation = animationDefault;
	//animationDefault->SetFrame(0, 0);
}

void BallTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	/*x += dx;
	y += dy;*/
}

BallTrap::~BallTrap()
{
}
