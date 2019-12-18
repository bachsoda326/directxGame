#include "Boss.h"

Boss * Boss::__instance = NULL;

Boss::Boss()
{
}

Boss::Boss(float left, float top, float width, float height)
{	
	x = left + 22;
	y = top + 71;
	w = width;
	h = height;

	collType = CollEnemy;
	objType = OBJBoss;	
	isCreate = false;
	isHurt = false;
	isDie = false;
	isDead = false;
	direction = true;
	typeBoss = 0;
	blood = 18;
	vx = 0;
	vy = 0;
}

Boss * Boss::GetInstance()
{
	if (__instance == NULL) __instance = new Boss();
	return __instance;
}

void Boss::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBoss = Textures::GetInstance()->Get(ID_TEX_BOSS);

	animationMan = new Animation("Jafar", XML_BOSS_ANIMATION_PATH, texBoss, 100);
	animationSnake = new Animation("Jafar_Snake", XML_BOSS_ANIMATION_PATH, texBoss, 100);

	SetState(STANDING);
	currentAnimation = animationMan;
	animationMan->SetFrame(0, 0);	

	startCut = GetTickCount();
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (blood > 10)
		typeBoss = 0;
	else
		typeBoss = 1;

	if (isDie)
	{
		Die();
		return;
	}

	switch (state)
	{
	case ATTACK:
		if (Aladdin::GetInstance()->GetState() == Aladdin::RESETPOSITION || Aladdin::GetInstance()->GetState() == Aladdin::DIE)
			Stand();
		else
			Attack();
		break;
	default:
		Stand();
		break;
	}

	for (int i = 0; i < list.size(); i++)
	{
		list[i]->Update(dt);
	}
}

void Boss::Render()
{
	GameObject::Render();

	for (int i = 0; i < list.size(); i++)
	{
		list[i]->Render();
	}
}

void Boss::SetAnimation(BossAnimations ani)
{
	switch (ani)
	{
	case ANI_SNAKE:
	{
		//reset frame when press event
		currentAnimation = animationSnake;
		currentAnimation->ResetFrame();
		break;
	}
	default:
		currentAnimation = animationMan;
		currentAnimation->ResetFrame();
		break;
	}
}

void Boss::Stand()
{
	switch (state)
	{
	case STANDING:
		break;
	default:
	{
		SetState(STANDING);
		if (typeBoss == 0)
		{
			SetAnimation(ANI_MAN);
			animationMan->SetFrame(0, 0);
		}
		else
		{
			SetAnimation(ANI_SNAKE);
			animationMan->SetFrame(0, 0);
		}
		break;
	}
	}
}

void Boss::Attack()
{
	switch (state)
	{
	case ATTACK:
	{
		if (typeBoss == 0)
		{
			if (currentAnimation == animationMan && currentAnimation->GetCurrentFrame() == 6 /*&& isCreate == false*/)
			{
				DWORD endCut = GetTickCount();
				if (endCut - startCut > 150)
				{
					startCut = GetTickCount();
					CreateStar();
				}
			}
			if (currentAnimation == animationMan && currentAnimation->GetCurrentFrame() == 6)
				animationMan->SetFrame(6, 6);
		}
		else
		{
			if (currentAnimation == animationSnake && currentAnimation->GetCurrentFrame() == 9 && isCreate == false)
			{
				CreateFire();
				isCreate = true;
			}
			if (currentAnimation->isActionFinish())
				Stand();
			break;
		}
		break;
	}
	default:
	{
		isCreate = false;
		SetState(ATTACK);
		if (typeBoss == 0)
		{
			SetAnimation(ANI_MAN);
			animationMan->SetFrame(0, 7);
		}
		else
		{
			SetAnimation(ANI_SNAKE);
			animationSnake->SetFrame(0, 10);
		}
		break;
	}
	}
}

void Boss::Die()
{
	Enemy::Die();
}

void Boss::CreateFire()
{
	Fire* obj = new Fire();
	obj->GetBoss(this);
	obj->yDraw = (this->Bottom() + this->Top()) / 2 - 3;
	obj->vy = 1.0f;
	if (direction)
	{
		obj->xDraw = this->Right();
		obj->vx = 1.0f;
	}
	else
	{
		obj->xDraw = this->Left();
		obj->vx = -1.0f;
	}
	obj->direction = this->direction;
	obj->typeFire = 2;
	obj->LoadResources();
	list.push_back(obj);
}

vector<GameObject*>* Boss::GetList()
{
	return &list;;
}

void Boss::DeleteFire(GameObject * fire)
{
	for (int i = 0; i < list.size();)
	{
		if (list.at(i) == fire)
		{
			list.erase(list.begin() + i);
			delete fire;
			fire = nullptr;
			return;
		}
		else
			i++;
	}
}

void Boss::CreateStar()
{
	Star* obj = new Star();
	obj->GetBoss(this);
	obj->yDraw = (this->Bottom() + this->Top()) / 2 - 3;
	if (direction)
		obj->xDraw = this->Right() + 2;
	else
		obj->xDraw = this->Left() - 2;
	obj->direction = !this->direction;
	obj->LoadResources();
	list.push_back(obj);
}

void Boss::DeleteStar(GameObject * star)
{
	for (int i = 0; i < list.size();)
	{
		if (list.at(i) == star)
		{
			list.erase(list.begin() + i);
			delete star;
			star = nullptr;
			return;
		}
		else
			i++;
	}
}

void Boss::ChangeFrameSize(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		this->xDraw -= 700;
		this->w += 1400;
	}
}

void Boss::ResetFrameSize(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		this->xDraw += 700;
		this->w -= 1400;
	}
}

void Boss::OnCollision(GameObject * obj, float nx, float ny)
{	
}

void Boss::OnIntersect(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		if (Aladdin::GetInstance()->GetState() == Aladdin::CUTTING && !isHurt)
		{
			if ((obj->direction && obj->Right() > this->Left() && obj->x < this->x) || (!obj->direction && obj->Left() < this->Right() && obj->x > this->x))
			{
				blood--;
				GameSound::getInstance()->play(JAFAR_HURT_MUSIC);
			}
			if (blood == 0)
			{
				Die();
				state = DIE;
				return;
			}
			isHurt = true;
		}
		if (Aladdin::GetInstance()->GetState() != Aladdin::CUTTING)
			isHurt = false;
		if (x < obj->x)
		{
			direction = true;
		}
		else
		{
			direction = false;
		}
		if ((obj->x > this->Right() - 20 && obj->x < this->Left() + 20) || (obj->x > this->x - 20 && obj->x < this->x + 20))
			Stand();
		else
			Attack();

		//if (obj->GetAttack())
		//{
		//	blood--;
		//	GameSound::getInstance()->play(BOSS_HURT_MUSIC);
		//}
	}
	if (obj->collType == CollApple)
	{
		blood--;
		GameSound::getInstance()->play(JAFAR_HURT_MUSIC);
		if (blood == 0)
		{
			Die();
			state = DIE;
			return;
		}
	}
}


Boss::~Boss()
{
}
