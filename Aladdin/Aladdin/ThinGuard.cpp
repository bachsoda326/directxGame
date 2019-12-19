#include "ThinGuard.h"
#include "Textures.h"

ThinGuard::ThinGuard(float Left, float top, float width, float height)
{
	xDraw = Left;
	yDraw = top;
	x = xDraw + 20;
	y = yDraw + 62;
	isDie = false;
	isDead = false;
	direction = true;
	blood = 2;
	collType = CollEnemy;
	objType = OBJThinGuard;
}

void ThinGuard::LoadResources()
{
	LPDIRECT3DTEXTURE9 texGuards = Textures::GetInstance()->Get(ID_TEX_GUARDS);
	// khởi tạo các animation
	animationRun = new Animation("Run", XML_THINGUARD_ANIMATION_PATH, texGuards, 100);
	animationCut_1 = new Animation("Cut_1", XML_THINGUARD_ANIMATION_PATH, texGuards, 100);
	animationHurt = new Animation("Hurt", XML_THINGUARD_ANIMATION_PATH, texGuards, 90);
	animationDie = new Animation("Animation", XML_ENEMYDEAD_ANIMATION_PATH, texGuards, 100);
	// animation ban đầu
	currentAnimation = animationCut_1;
	animationCut_1->SetFrame(5, 5);
}

void ThinGuard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	// khi c.bị chết thì chết
	if (isDie)
	{
		Die();
		return;
	}
	// update action theo tr.thái hiện tại
	switch (state)
	{
	case CUTTING_1:
		Cut();
		break;
	case RUNNING:
		Run();
		break;
	case HURT:
		Hurt();
		break;
	default:
		Stand();
		break;
	}
}

void ThinGuard::SetAnimation(ThinGuardAnimations ani)
{
	switch (ani)
	{
	case ANI_RUN:
	{		
		currentAnimation = animationRun;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_1:
	{
		currentAnimation = animationCut_1;
		animationCut_1->SetFrame(0, 5);
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_HURT:
	{
		currentAnimation = animationHurt;
		animationHurt->SetFrame(0, 8);
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_DIE:
	{
		currentAnimation = animationDie;
		currentAnimation->ResetFrame();
		break;
	}
	}
}

void ThinGuard::Cut()
{
	switch (state)
	{
	case CUTTING_1:
		if (currentAnimation->isActionFinish())
			GameSound::getInstance()->play(GUARD_CUT_MUSIC);		
		break;
	default:
	{		
		SetState(CUTTING_1);
		SetAnimation(ANI_CUT_1);
		vx = 0;
		break;
	}
	}
}

void ThinGuard::Run()
{
	switch (state)
	{
	case RUNNING:
		break;
	default:
	{
		SetState(RUNNING);
		SetAnimation(ANI_RUN);
		if (direction)
			vx = -0.2f;
		else
			vx = 0.2f;
		break;
	}
	}
}

void ThinGuard::Stand()
{
	switch (state)
	{
	case STANDING:
		break;
	default:
	{
		/*if (status == HURT && !currentAnimation->isActionFinish())
			break;*/
		SetState(STANDING);
		SetAnimation(ANI_HURT);
		animationHurt->SetFrame(0, 0);
		vx = 0;
		break;
	}
	}
}

void ThinGuard::Hurt()
{
	switch (state)
	{
	case HURT:
	{
		if (currentAnimation->isActionFinish())
			Stand();
		break;
	}
	default:
	{
		SetState(HURT);
		SetAnimation(ANI_HURT);
		vx = 0;
		blood--;
		GameSound::getInstance()->play(THINGUARD_HURT_MUSIC);
		if (blood == 0)
		{
			Die();
			SetState(DIE);
			// cộng điểm
			Aladdin::GetInstance()->score += 5;
		}
		break;
	}
	}
}

void ThinGuard::Die()
{
	Enemy::Die();
}

void ThinGuard::ChangeFrameSize(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		xDraw -= 200;
		w += 400;
	}
}

void ThinGuard::ResetFrameSize(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		xDraw += 200;
		w -= 400;
	}
}

void ThinGuard::OnIntersect(GameObject * obj)
{
	if (obj->collType == CollApple)
	{
		SetState(STANDING);
		Hurt();
	}

	if (obj->collType == CollAladdin)
	{
		if (Aladdin::GetInstance()->GetState() == Aladdin::CUTTING)
		{
			if ((obj->direction && obj->Right() > this->Left() && obj->x < this->x) || (!obj->direction && obj->Left() < this->Right() && obj->x > this->x))
				Hurt();
		}
		else if (state != HURT)
		{
			if (obj->x < this->x)
				direction = true;
			else
				direction = false;

			if (this->x - 100 <= obj->x && obj->x <= this->x + 100 && this->Top() <= obj->Bottom() - 8 && this->Bottom() > obj->Top() + 8)
				Cut();
			/*else if (this->x - 200 <= obj->x && obj->x <= this->x + 200)
				Run();*/
			else
				Stand();
		}
	}
}

ThinGuard::~ThinGuard()
{
}
