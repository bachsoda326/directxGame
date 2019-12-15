#include "BoomSkeleton.h"
#include "Textures.h"
#include "Bone.h"

BoomSkeleton::BoomSkeleton(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 26;
	y = yDraw + 78;
	isDead = false;
	blood = 1;
	direction = true;
	collType = CollEnemy;
	objType = OBJBoomSkeleton;
}

void BoomSkeleton::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBoomSkeleton = Textures::GetInstance()->Get(ID_TEX_BOOMSKELETON);

	animationDefault = new Animation("Animation", XML_BOOMSKELETON_ANIMATION_PATH, texBoomSkeleton, 100);

	currentAnimation = animationDefault;
	animationDefault->SetFrame(0, 0);
	SetState(STANDING);
}

void BoomSkeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	/*x += dx;
	y += dy;*/

	if (isDie)
	{
		Die();
		/*return;*/
	}

	switch (state)
	{	
	case DOING:
		Doing();
		break;	
	case HURT:
		Hurt();
		break;
	default:
		Stand();
		break;
	}

	currentTime = GetTickCount();

	if (currentTime - startTime > 3000)
		DeleteListBones();

	for (int i = 0; i < listBones.size(); i++)
	{
		listBones[i]->Update(dt);
		Collision::CheckCollision(Aladdin::GetInstance(), listBones[i]);
	}
}

void BoomSkeleton::Render()
{
	GameObject::Render();

	for (int i = 0; i < listBones.size(); i++)
	{
		listBones[i]->Render();
	}
}

void BoomSkeleton::Stand()
{
	SetState(STANDING);
	animationDefault->SetFrame(0, 0);
}

void BoomSkeleton::Doing()
{
	switch (state)
	{
	case DOING:
	{
		if (currentAnimation->isActionFinish())
		{
			GameSound::getInstance()->play(BOOMSKELETON_MUSIC);
			Die();
			CreateBone();
			SetState(DIE);
		}
		break;
	}
	default:
		SetState(DOING);
		animationDefault->SetFrame(1, 19);
		break;
	}	
}

void BoomSkeleton::Hurt()
{
	switch (state)
	{
	case HURT:
	{
		/*if (currentAnimation->isActionFinish())
			Stand();*/
		break;
	}
	default:
	{
		SetState(HURT);		
		vx = 0;
		blood--;
		/*if (blood == 1)
			GameSound::getInstance()->play(GUARD_HIT_MUSIC);*/
		if (blood == 0)
		{
			Die();
			SetState(DIE);
		}
		break;
	}
	}
}

void BoomSkeleton::Die()
{
	Enemy::Die();
}

vector<GameObject*>* BoomSkeleton::GetListBones()
{
	return &listBones;
}

void BoomSkeleton::CreateBone()
{
	startTime = GetTickCount();

	Bone* bone1 = new Bone();
	bone1->xDraw = (this->Right() + this->Left()) / 2;
	bone1->yDraw = (this->Top() + this->Bottom()) / 2;
	bone1->vx = -0.25f;
	bone1->LoadResources();
	listBones.push_back(bone1);

	Bone* bone2 = new Bone();
	bone2->xDraw = (this->Right() + this->Left()) / 2;
	bone2->yDraw = (this->Top() + this->Bottom()) / 2;
	bone2->vx = -0.25f;
	bone2->vy = -0.25f;
	bone2->LoadResources();
	listBones.push_back(bone2);

	Bone* bone3 = new Bone();
	bone3->xDraw = (this->Right() + this->Left()) / 2;
	bone3->yDraw = (this->Top() + this->Bottom()) / 2;
	bone3->vy = -0.3f;
	bone3->LoadResources();
	listBones.push_back(bone3);

	Bone* bone4 = new Bone();
	bone4->xDraw = (this->Right() + this->Left()) / 2;
	bone4->yDraw = (this->Top() + this->Bottom()) / 2;
	bone4->vx = 0.25f;
	bone4->vy = -0.25f;
	bone4->LoadResources();
	listBones.push_back(bone4);

	Bone* bone5 = new Bone();
	bone5->xDraw = (this->Right() + this->Left()) / 2;
	bone5->yDraw = (this->Top() + this->Bottom()) / 2;
	bone5->vx = 0.25f;
	bone5->LoadResources();
	listBones.push_back(bone5);	
}

void BoomSkeleton::DeleteListBones()
{
	listBones.clear();
}

void BoomSkeleton::DeleteBone(GameObject *bone)
{
	for (int i = 0; i < listBones.size(); i++)
	{
		if (listBones[i] == bone)
		{
			listBones.erase(listBones.begin() + i);
			delete bone;
			bone = 0;
		}
	}
}

void BoomSkeleton::ChangeFrameSize(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		xDraw -= 250;
		yDraw -= 250;
		w += 500;
		h += 500;
	}
}

void BoomSkeleton::ResetFrameSize(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		xDraw += 250;
		yDraw += 250;
		w -= 500;
		h -= 500;
	}
}

void BoomSkeleton::OnIntersect(GameObject * obj)
{
	if (obj->collType == CollApple)
	{
		SetState(DIE);
		Die();
		return;
	}
	if (obj->collType == CollAladdin)
	{
		if (Aladdin::GetInstance()->GetState() == Aladdin::CUTTING)
		{
			if (((obj->Right() > this->Left() && obj->x < this->x) || (obj->Left() < this->Right() && obj->x > this->x)) && (obj->Top() < this->Bottom() && obj->Bottom() > this->Top()))
				Hurt();
			return;
		}

		if (this->x - 120 <= obj->x && obj->x <= this->x + 120 && this->y + 35 >= obj->Top())
			Doing();
		else if (state == DOING && (this->x - 200 >= obj->x || obj->x >= this->x + 200))
			Stand();
	}
}

BoomSkeleton::~BoomSkeleton()
{
}
