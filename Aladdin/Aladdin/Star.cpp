#include "Star.h"

Star::Star()
{
	isDead = false;
	collType = CollStar;
	objType = OBJStar;
}

Star::~Star()
{
}

void Star::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBoss = Textures::GetInstance()->Get(ID_TEX_BOSS);

	animationFling = new Animation("Star", XML_BOSSATTACK_ANIMATION_PATH, texBoss, 100);
	animationDestroy = new Animation("Star_Hit", XML_BOSSATTACK_ANIMATION_PATH, texBoss, 100);

	currentAnimation = animationFling;
	SetState(FLING);

	x = xDraw + 14;
	y = yDraw + 6;
	nx = 0;
	ny = 0;
}

void Star::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	
	x += dx;
	y += dy;

	switch (state)
	{
	case DESTROY:
		Destroy();
		break;
	default:
		Fly();
		break;
	}
}

void Star::SetAnimation(StarAnimations ani)
{
	switch (ani)
	{
	case ANI_DESTROY:
	{		
		currentAnimation = animationDestroy;
		currentAnimation->ResetFrame();
		break;
	}
	default:
		currentAnimation = animationFling;
		currentAnimation->ResetFrame();
		break;
	}
}

void Star::GetBoss(Boss * obj)
{
	boss = obj;
}

void Star::Destroy()
{
	switch (state)
	{
	case DESTROY:
	{
		if (currentAnimation->isActionFinish())
		{
			vx = 0;
			vy = 0;
			isDead = true;
			boss->DeleteStar(this);
		}
		break;
	}
	default:
	{
		SetState(DESTROY);
		SetAnimation(ANI_DESTROY);
		vx = 0;
		vy = 0;
		isDie = true;
		break;
	}
	}
}

void Star::Fly()
{
	switch (state)
	{
	case FLING:
	{
		float max;
		vx = ((Aladdin::GetInstance()->Left() + Aladdin::GetInstance()->Right()) / 2 - this->x);
		vy = ((Aladdin::GetInstance()->Top() + Aladdin::GetInstance()->Bottom()) / 2 - this->y);
		max = (abs(vx) > abs(vy)) ? abs(vx) : abs(vy);
		vx = vx / max;
		vy = vy / max;
		break;
	}
	default:
	{
		state = FLING;
		SetAnimation(ANI_FLING);
		break;
	}
	}
}

void Star::OnCollision(GameObject * obj, float nx, float ny)
{
}

void Star::OnIntersect(GameObject * obj)
{
	if (obj->collType == CollAladdin && !isDie)
	{
		if (this->x > obj->Left() && this->x < obj->Right())
		{
			obj->vx -= this->vx / 20;
			Destroy();
		}
	}
}
