#include "BoomSkeleton.h"
#include "Textures.h"

BoomSkeleton::BoomSkeleton(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 26;
	y = yDraw + 78;
	isDead = false;
	direction = true;
	collType = CollEnemy;
	objType = OBJBoomSkeleton;
}

void BoomSkeleton::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBoomSkeleton = Textures::GetInstance()->Get(ID_TEX_BOOMSKELETON);

	animationDefault = new Animation("Animation", XML_BOOMSKELETON_ANIMATION_PATH, texBoomSkeleton, 100);

	currentAnimation = animationDefault;
	//animationDefault->SetFrame(0, 0);
}

void BoomSkeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	/*x += dx;
	y += dy;*/
}

BoomSkeleton::~BoomSkeleton()
{
}
