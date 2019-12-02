#include "StoneBrick.h"
#include "Textures.h"

StoneBrick::StoneBrick(float left, float top, float width, float height)
{
	x = left;
	y = top;
	/*xDraw = left;
	yDraw = top;
	w = width;
	h = height;	*/
	direction = true;
	collType = CollBrick;
}

void StoneBrick::LoadResources(bool check)
{
	LPDIRECT3DTEXTURE9 texBrickTrap = Textures::GetInstance()->Get(ID_TEX_BRICK_TRAP);

	animationDefault = new Animation("Animation", XML_STONEBRICK_ANIMATION_PATH, texBrickTrap, 130);

	currentAnimation = animationDefault;
	if (check)
		animationDefault->SetFrame(0, 4);
	else
		animationDefault->SetFrame(4, 0);

	startTime = GetTickCount();
}

void StoneBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	/*x += dx;
	y += dy;*/
}

void StoneBrick::Render()
{
	DWORD startWait = GetTickCount();
	int i = currentAnimation->GetCurrentFrame();
	if (i == 0)
	{
		animationDefault->SetFrame(0, 0);

		if (startWait - startTime > 2500)
		{
			animationDefault->SetFrame(1, 4);
			startTime = GetTickCount();
		}
	}
	if (i == 4)
	{
		animationDefault->SetFrame(4, 4);

		if (startWait - startTime > 2500)
		{
			animationDefault->SetFrame(3, 0);
			startTime = GetTickCount();
		}
	}

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

void StoneBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = xDraw;
	top = yDraw;
	right = xDraw + w - 3;
	bottom = yDraw + 15;
}

StoneBrick::~StoneBrick()
{
}
