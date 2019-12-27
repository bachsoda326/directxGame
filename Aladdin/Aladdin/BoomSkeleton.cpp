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
	blood = SKELETON_BLOOD;
	direction = true;
	isBlink = 0;
	collType = CollEnemy;
	objType = OBJBoomSkeleton;
}

void BoomSkeleton::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBoomSkeleton = Textures::GetInstance()->Get(ID_TEX_BOOMSKELETON);
	// khởi tạo các animation
	animationDefault = new Animation("Animation", XML_BOOMSKELETON_ANIMATION_PATH, texBoomSkeleton, 100);
	// animation ban đầu
	currentAnimation = animationDefault;
	animationDefault->SetFrame(0, 0);
	SetState(STANDING);
}

void BoomSkeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	for (int i = 0; i < listBones.size(); i++)
	{
		listBones[i]->Update(dt);
		// xét collision giữa xương đc tạo ra vs Aladdin
		Collision::CheckCollision(Aladdin::GetInstance(), listBones[i]);
	}

	// khi c.bị chết thì chết
	if (isDie)
	{
		Die();		
		return;
	}
	// update action theo tr.thái hiện tại
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
}

void BoomSkeleton::Render()
{
	if (!isDead && isBlink != 1)
	{
		// Vector trans giúp dời ảnh theo camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, trans);
	}

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
			// tạo xương khi nổ
			CreateBone();
			SetState(DIE);
		}
		break;
	}
	default:
		SetState(DOING);
		int i = currentAnimation->GetCurrentFrame();
		animationDefault->SetFrame(i, 19);
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
		blood -= ALADDIN_DAMAGE_BOOMSKELETON;
		/*if (blood == 1)
			GameSound::getInstance()->play(GUARD_HIT_MUSIC);*/
		if (blood <= 0)
		{
			startTime = GetTickCount();
			Die();
			SetState(DIE);
			// cộng điểm
			Aladdin::GetInstance()->score += ALADDIN_SCORE_BOOMSKELETON;
		}
		break;
	}
	}
}

void BoomSkeleton::Die()
{
	if (!isDie)
	{
		currentAnimation = animationDie;
		vy = 0;
		vx = 0;
		y = (this->Top() + this->Bottom()) / 2;
		isDie = true;
	}
	else
	{		
		if (currentAnimation->isActionFinish())
		{
			isBlink = 1;
		}
		// sau t giây sẽ xóa list xương
		currentTime = GetTickCount();
		if (currentTime - startTime > 1300)
			DeleteListBones();
	}
}

vector<GameObject*>* BoomSkeleton::GetList()
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

	// tạo xương 6, vx ngang vy dọc
	//Bone* bone6 = new Bone();
	//bone6->xDraw = (this->Right() + this->Left()) / 2;
	//bone6->yDraw = (this->Top() + this->Bottom()) / 2;
	////bone6->vx = 0.25f;
	//bone4->vy = 0.15f;
	//bone6->LoadResources();
	//listBones.push_back(bone6);
}

void BoomSkeleton::DeleteListBones()
{
	listBones.clear();
	isDead = true;
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
		Hurt();

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
