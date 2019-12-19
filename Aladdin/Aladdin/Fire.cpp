#include "Fire.h"

Fire::Fire()
{
	collType = CollEnemy;
	objType = OBJFire;
}

void Fire::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBoss = Textures::GetInstance()->Get(ID_TEX_BOSS);
	// khởi tạo các animation
	animationBurn = new Animation("Burn", XML_FIRE_ANIMATION_PATH, texBoss, 100);
	animationFire = new Animation("Fire", XML_FIRE_ANIMATION_PATH, texBoss, 100);
	// animation ban đầu
	if (typeFire == 1)
		currentAnimation = animationBurn;
	else
	{
		currentAnimation = animationFire;
		animationFire->SetFrame(0, 0);
	}
	SetState(MOVING);

	x = xDraw + 12;
	y = yDraw;
	vx = 0;
	vy = 0;
}

void Fire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// update v.trí di chuyển vs v.tốc hiện tại
	GameObject::Update(dt);
	x += dx;
	y += dy;

	// update action theo tr.thái hiện tại
	switch (state)
	{
	case DESTROY:
		Destroy();
		return;
	default:
		Move();
		break;
	}

	// v.tốc rơi (khi là lửa Boss phun)
	if (typeFire == 2)
		vy += 0.1f;
}

void Fire::SetAnimation(FireAnimations ani)
{
	switch (ani)
	{
	case ANI_BURN:
	{		
		currentAnimation = animationBurn;
		currentAnimation->ResetFrame();
		break;
	}
	default:
		currentAnimation = animationFire;
		currentAnimation->ResetFrame();
		break;
	}
}

void Fire::GetFireCarpet(FireCarpet * obj)
{
	this->fireCarpet = obj;
}

void Fire::GetBoss(Boss * obj)
{
	this->boss = obj;
}

void Fire::Move()
{
	switch (state)
	{
	case MOVING:
	{
		if (typeFire == 1 && currentAnimation->isActionFinish())
			Destroy();		
		if (typeFire == 2 && ny == -1.0f && currentAnimation == animationFire && currentAnimation->GetLastFrame() == 0)
		{
			SetAnimation(ANI_FIRE);
			animationFire->SetFrame(0, 7);
			if (direction)
				vx = 0.2f;
			else
				vx = -0.2f;
			vy = 0;
		}
		break;
	}
	default:
	{
		SetState(MOVING);
		if (typeFire == 1)
		{
			SetAnimation(ANI_BURN);
			vx = 0;
		}
		else
		{
			SetAnimation(ANI_FIRE);
			animationFire->SetFrame(0, 0);
		}
		break;
	}
	}
}

void Fire::Destroy()
{
	switch (state)
	{
	case DESTROY:
	{
		isDead = true;
		vx = 0;
		vy = 0;
		// xác định xem là lửa của thảm hay lửa của Boss rồi xóa
		if (fireCarpet != NULL)
			fireCarpet->DeleteFire(this);
		else if (boss != NULL)
			boss->DeleteFire(this);
		break;
	}
	default:
	{
		SetState(DESTROY);
		break;
	}
	}
}

void Fire::OnCollision(GameObject * obj, float nx, float ny)
{
	switch (obj->collType)
	{
	case CollGround: case CollFence:
	{
		Collision::PreventMove(this, obj, nx, ny);
		if (nx != 0 && state != DESTROY && typeFire == 2)
			Destroy();
		break;
	}
	}
}

void Fire::OnIntersect(GameObject * obj)
{
}


Fire::~Fire()
{
}
