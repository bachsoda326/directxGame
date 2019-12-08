#include "Item.h"



Item::Item()
{
	LPDIRECT3DTEXTURE9 texItemActived = Textures::GetInstance()->Get(ID_TEX_ITEMACTIVED);

	animationItemActived = new Animation("Animation", XML_ITEMACTIVED_ANIMATION_PATH, texItemActived, 100);
}

void Item::LoadResources()
{
	state = NONACTIVED;	
	direction = true;
	isDead = false;
	isDie = false;
	isActived = false;
	nx = 0.0f;
	ny = 0.0f;
	vx = 0;
	vy = 0;
	startWait = GetTickCount();
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;

	switch (state)
	{
	case ACTIVED:
		Active();
		break;
	case NONACTIVED:
		NonActive();
		break;
	}
}

void Item::OnCollision(GameObject * obj, float nx, float ny)
{
}

void Item::OnIntersect(GameObject * obj)
{
	if (obj->collType == CollAladdin && state != ACTIVED)
		Active();
}

void Item::Active()
{
	switch (state)
	{
	case ACTIVED:
	{
		//Thực hiện animation actived xong đặt isDead = true để xóa item ra khỏi danh sách
		if (currentAnimation->isActionFinish())
			isDead = true;
		break;
	}
	default:
	{
		SetState(ACTIVED);
		currentAnimation = animationItemActived;		
		vy = 0;
		vx = 0;
		x = (this->Left() + this->Right()) / 2;
		y = (this->Top() + this->Bottom()) / 2;
		isDie = true;
		isActived = true;
		break;
	}
	}
}

void Item::NonActive()
{
}


Item::~Item()
{
}
