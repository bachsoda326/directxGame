#include "Bone.h"

Bone::Bone()
{
	isDead = false;
	collType = CollEnemy;
	objType = OBJBone;
}

void Bone::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBoomSkeleton = Textures::GetInstance()->Get(ID_TEX_BOOMSKELETON);

	animationDefault = new Animation("Bone", XML_BOOMSKELETON_ANIMATION_PATH, texBoomSkeleton, 100);

	currentAnimation = animationDefault;

	x = xDraw;
	y = yDraw;
}

void Bone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;

	vy += 0.01f;
}

Bone::~Bone()
{
}
