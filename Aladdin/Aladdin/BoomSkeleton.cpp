#include "BoomSkeleton.h"
#include "Textures.h"

BoomSkeleton::BoomSkeleton(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 26;
	y = yDraw + 78;
	direction = true;
	collType = CollEnemy;
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

void BoomSkeleton::Render()
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

BoomSkeleton::~BoomSkeleton()
{
}
