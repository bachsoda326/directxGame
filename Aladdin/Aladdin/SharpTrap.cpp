#include "SharpTrap.h"
#include "Textures.h"

SharpTrap::SharpTrap(float left, float top, float width, float height)
{
	x = left;
	y = top;
	
	direction = true;
	collType = CollEnemy;
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

void SharpTrap::Render()
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

SharpTrap::~SharpTrap()
{
}
