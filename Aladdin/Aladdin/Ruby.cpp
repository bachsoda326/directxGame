﻿#include "Ruby.h"
#include "Textures.h"

Ruby::Ruby()
{
	collType = CollUnknown;
	isDead = false;
	direction = true;
}

Ruby::Ruby(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 8;
	y = yDraw + 8;
	isDead = false;
	direction = true;
	collType = CollItem;
	objType = OBJRuby;
}

void Ruby::LoadResources()
{
	LPDIRECT3DTEXTURE9 texItems = Textures::GetInstance()->Get(ID_TEX_ITEM);

	animationDefault = new Animation("Animation", XML_RUBY_ANIMATION_PATH, texItems, 100);

	currentAnimation = animationDefault;	
	if (collType == CollUnknown)
		animationDefault->SetFrame(9, 9);

	Item::LoadResources();
}

void Ruby::Render()
{
	if (collType == CollUnknown)
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0));
	else if (!isDead)
	{
		// // Vector trans giúp dời ảnh theo camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, trans);
	}
}

void Ruby::Active()
{
	Item::Active();
}

void Ruby::NonActive()
{	
	if (collType != CollUnknown && currentAnimation->isActionFinish())
	{
		DWORD endWait = GetTickCount();
		if (endWait - startWait > 3500)
		{
			animationDefault->SetFrame(0, 8);
			startWait = GetTickCount();
		}
		else
		{
			animationDefault->SetFrame(0, 0);
		}
	}
}

Ruby::~Ruby()
{
}
