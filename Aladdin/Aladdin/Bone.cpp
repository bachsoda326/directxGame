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
	// khởi tạo các animation
	animationDefault = new Animation("Bone", XML_BOOMSKELETON_ANIMATION_PATH, texBoomSkeleton, 100);
	// animation ban đầu
	currentAnimation = animationDefault;

	x = xDraw;
	y = yDraw;
}

void Bone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// update v.trí di chuyển vs v.tốc hiện tại
	GameObject::Update(dt);
	x += dx;
	y += dy;
	// v.tốc rơi
	vy += 0.01f;
}

Bone::~Bone()
{
}
