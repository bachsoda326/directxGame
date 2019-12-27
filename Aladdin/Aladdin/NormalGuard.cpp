#include "NormalGuard.h"
#include "Textures.h"

NormalGuard::NormalGuard(float Left, float top, float width, float height)
{
	xDraw = Left;
	yDraw = top;
	x = xDraw + 24;
	y = yDraw + 59;	
	isDie = false;
	isDead = false;
	direction = true;
	blood = NORMALGUARD_BLOOD;
	collType = CollEnemy;
	objType = OBJNormalGuard;
}

void NormalGuard::LoadResources()
{
	LPDIRECT3DTEXTURE9 texGuards = Textures::GetInstance()->Get(ID_TEX_GUARDS);
	// khởi tạo các animation
	animationIdle = new Animation("Idle", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 300);
	animationRun = new Animation("Run", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 300);
	animationRunOnFire = new Animation("RunOnFire", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 100);
	animationCut_1 = new Animation("Cut_1", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 100);
	animationCut_2 = new Animation("Cut_2", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 100);
	animationHurt = new Animation("Hurt", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 50);
	// animation ban đầu
	currentAnimation = animationIdle;
	//animationIdle->SetFrame(0, 0);
}

void NormalGuard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//GameObject::Update(dt);
	/*x += dx;
	y += dy;*/

	// khi c.bị chết thì chết
	if (isDie)
	{
		Die();
		return;
	}
	// update action theo tr.thái hiện tại
	switch (state)
	{
	case PROVOKE:
		Provoke();
		break;	
	case CUTTING_1: case CUTTING_2:
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

void NormalGuard::SetAnimation(NormalGuardAnimations ani)
{
	switch (ani)
	{
	case ANI_IDLE:
	{		
		currentAnimation = animationIdle;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_RUN:
	{
		currentAnimation = animationRun;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_RUN_ON_FIRE:
	{
		currentAnimation = animationRunOnFire;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_1:
	{
		currentAnimation = animationCut_1;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_2:
	{
		currentAnimation = animationCut_2;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_HURT:
	{
		currentAnimation = animationHurt;
		currentAnimation->ResetFrame();
		break;
	}
	}
}

void NormalGuard::Cut()
{
	switch (state)
	{
	case CUTTING_2:
	{
		if (currentAnimation->isActionFinish())
		{
			GameSound::getInstance()->play(GUARD_CUT_MUSIC);
		}
		// sau t.gian ngẫu nhiên sẽ đổi animation chém
		srand(time(0));
		if (currentAnimation->isActionFinish() && rand() % 3 == 1)
		{
			GameSound::getInstance()->play(GUARD_CUT_MUSIC);
			SetState(CUTTING_1);
			SetAnimation(ANI_CUT_1);
			/*Cut();*/
		}
		break;
	}
	case CUTTING_1:
	{
		if (currentAnimation->isActionFinish())
		{
			GameSound::getInstance()->play(GUARD_CUT_MUSIC);
			SetState(CUTTING_2);
			SetAnimation(ANI_CUT_2);
			vx = 0;
		}
		break;
	}
	default:
	{		
		SetState(CUTTING_2);
		SetAnimation(ANI_CUT_2);
		vx = 0;
		break;
	}
	}
}

void NormalGuard::Run()
{

}

void NormalGuard::Stand()
{
	switch (state)
	{
	case STANDING:
		break;
	default:
	{
		SetState(STANDING);
		SetAnimation(ANI_CUT_1);
		animationCut_1->SetFrame(0, 0);		
		vx = 0;
		break;
	}
	}
}

void NormalGuard::Hurt()
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
		blood -= ALADDIN_DAMAGE_NORMALGUARD;
		GameSound::getInstance()->play(NORMALGUARD_HURT_MUSIC);
		if (blood <= 0)
		{
			Die();
			SetState(DIE);
			// cộng điểm
			Aladdin::GetInstance()->score += ALADDIN_SCORE_NORMALGUARD;
		}
		break;
	}
	}
}

void NormalGuard::Provoke()
{
	switch (state)
	{
	case PROVOKE:
	{
		if (currentAnimation->isActionFinish() && currentAnimation->GetFirstFrame() == 0)
			animationIdle->SetFrame(2, 5);
		break;
	}
	default:
	{
		SetState(PROVOKE);
		SetAnimation(ANI_IDLE);
		vx = 0;
		break;
	}
	}
}

void NormalGuard::Die()
{
	Enemy::Die();
}

void NormalGuard::ChangeFrameSize(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		xDraw -= 250;
		w += 500;
	}
}

void NormalGuard::ResetFrameSize(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		xDraw += 250;
		w -= 500;
	}
}

void NormalGuard::OnIntersect(GameObject * obj)
{
	if (obj->collType == CollApple)
		Hurt();

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

			if (this->x - 115 <= obj->x && obj->x <= this->x + 115 && this->Top() <= obj->Bottom() - 8 && this->Bottom() > obj->Top() + 8)
				Cut();
			else if (this->x - 150 <= obj->x && obj->x <= this->x + 150)
				Provoke();
			/*else if (this->x - 230 <= obj->x && obj->x <= this->x + 230)
				Run();*/
			else
				Stand();
		}
	}
}

NormalGuard::~NormalGuard()
{
}
