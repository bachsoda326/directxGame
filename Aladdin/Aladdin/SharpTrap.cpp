#include "SharpTrap.h"
#include "Textures.h"

SharpTrap::SharpTrap(float left, float top, float width, float height)
{
	x = left;
	y = top;
	isDead = false;
	direction = true;
	collType = CollEnemy;
	objType = OBJSharpTrap;
}

void SharpTrap::LoadResources()
{
	LPDIRECT3DTEXTURE9 texSharpTrap = Textures::GetInstance()->Get(3);

	animationDefault = new Animation("Animation", XML_SHARPTRAP_ANIMATION_PATH, texSharpTrap, 200);

	currentAnimation = animationDefault;
	//animationDefault->SetFrame(0, 0);
}

void SharpTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	/*x += dx;
	y += dy;*/
}

SharpTrap::~SharpTrap()
{
}
