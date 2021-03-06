﻿#include "SharpTrap.h"
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
	// khởi tạo các animation
	animationDefault = new Animation("Animation", XML_SHARPTRAP_ANIMATION_PATH, texSharpTrap, 80);
	// animation ban đầu
	currentAnimation = animationDefault;
	//animationDefault->SetFrame(0, 0);
}

void SharpTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
}

void SharpTrap::Render()
{
	DWORD startWait = GetTickCount();
	int i = currentAnimation->GetCurrentFrame();
	if (i == 0)
	{
		animationDefault->SetFrame(0, 0);
		// sau t giây sẽ chọt ra
		if (startWait - startTime > 6000)
		{
			GameSound::getInstance()->play(SHARPTRAP_MUSIC);
			animationDefault->SetFrame(1, 5);
			startTime = GetTickCount();
		}
	}
	if (i == 5)
	{
		animationDefault->SetFrame(5, 5);
		// sau t gian sẽ thụt vào
		if (startWait - startTime > 1500)
		{
			animationDefault->SetFrame(4, 0);
			startTime = GetTickCount();
		}
	}

	GameObject::Render();
}

SharpTrap::~SharpTrap()
{
}
