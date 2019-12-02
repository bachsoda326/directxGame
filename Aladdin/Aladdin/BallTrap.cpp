#include "BallTrap.h"
#include "Textures.h"

BallTrap::BallTrap(float left, float top, float width, float height)
{
	x = left;
	y = top;
	
	direction = true;
	collType = CollUnknown;
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

void BallTrap::Render()
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

BallTrap::~BallTrap()
{
}
