﻿#include "FireCarpet.h"

FireCarpet::FireCarpet(float left, float top, float width, float height)
{	
	xDraw = left;
	yDraw = top;
	x = xDraw;
	y = yDraw;	
	w = width;
	h = height;

	isDie = false;
	isDead = false;
	objType = OBJFireCarpet;
	collType = CollGround;
}

void FireCarpet::LoadResources()
{	
	startDelay = GetTickCount();
}

void FireCarpet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < listFires.size(); i++)
	{
		listFires[i]->Update(dt);		
	}
}

void FireCarpet::Render()
{
	for (int i = 0; i < listFires.size(); i++)
	{
		listFires[i]->Render();
	}
}

void FireCarpet::CreateFire(GameObject * obj)
{
	Fire* fire = new Fire();
	fire->GetFireCarpet(this);
	fire->yDraw = obj->y;	
	fire->xDraw = obj->x - 24;
	fire->typeFire = 1;
	fire->LoadResources();
	listFires.push_back(fire);
}

vector<GameObject*>* FireCarpet::GetList()
{
	return &listFires;
}

void FireCarpet::DeleteFire(GameObject * fire)
{
	for (int i = 0; i < listFires.size();)
	{
		if (listFires[i] == fire)
		{
			listFires.erase(listFires.begin() + i);
			delete fire;
			fire = nullptr;
			return;
		}
		else
			i++;
	}
}

void FireCarpet::OnCollision(GameObject * obj, float nx, float ny)
{
}

void FireCarpet::OnIntersect(GameObject * obj)
{
	// sẽ xét giao nhau khi Boss là Rắn (typeBoss == 1)
	if (Boss::GetInstance()->typeBoss == 1 && obj->collType == CollAladdin && obj->y == this->Top())
	{
		if (obj->x > this->Left() && obj->x < this->Right())
		{
			// sau t giây sẽ tạo lửa
			DWORD endDelay = GetTickCount();
			if (endDelay - startDelay > 500)
			{
				GameSound::getInstance()->play(FIRE_MUSIC);
				CreateFire(obj);
				startDelay = endDelay;
			}
		}
	}
}

FireCarpet::~FireCarpet()
{
}
