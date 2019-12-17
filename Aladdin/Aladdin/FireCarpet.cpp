#include "FireCarpet.h"

FireCarpet::FireCarpet()
{
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
	/*if (obj->arx < this->left())
		fire->x = this->left() + 24;
	else if (obj->arx>this->right())
		fire->x = this->right() - 24;
	else*/
	fire->xDraw = obj->x - 24;
	fire->typeFire = 1;
	fire->LoadResources();
	listFires.push_back(fire);
}

vector<GameObject*>* FireCarpet::GetListFires()
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
	if (obj->collType == CollAladdin && obj->y == this->Top())
	{
		if (obj->x > this->Left() && obj->x < this->Right())
		{
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
