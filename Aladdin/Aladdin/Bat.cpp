#include "Bat.h"
#include "Textures.h"

Bat::Bat(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	xInit = xDraw;
	yInit = yDraw;
	x = xDraw + 3;
	y = yDraw + 16;
	isDead = false;
	direction = true;
	collType = CollEnemy;
	objType = OBJBat;
}

void Bat::LoadResources()
{
	LPDIRECT3DTEXTURE9 texBat = Textures::GetInstance()->Get(ID_TEX_BAT);

	animationStand = new Animation("Stand", XML_BAT_ANIMATION_PATH, texBat, 200);
	animationAttack = new Animation("Attack", XML_BAT_ANIMATION_PATH, texBat, 100);
	animationDieByApple = new Animation("DieByApple", XML_BAT_ANIMATION_PATH, texBat, 70);

	SetAnimation(ANI_STAND);
	animationStand->SetFrame(0, 0);
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	/*x += dx;
	y = yInit + 30*sin((2*M_PI*dt) + dy);*/

	

	if (isDie)
	{
		Die();
		return;
	}
	
	switch (state)
	{	
	case ATTACKING: case PREPARING:
		Attack();
		break;		
	default:
		Stand();
		break;
	}	
}

void Bat::SetAnimation(BatAnimations ani)
{
	switch (ani)
	{
	case ANI_STAND:
	{
		//reset frame when press event
		currentAnimation = animationStand;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_ATTACK:
	{
		currentAnimation = animationAttack;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_DIE_BY_APPLE:
	{
		currentAnimation = animationDieByApple;
		//currentAnimation->ResetFrame();
		break;
	}	
	}
}

void Bat::Stand()
{
	switch (state)
	{
	case STANDING:
		break;
	default:
	{
		SetState(STANDING);
		SetAnimation(ANI_STAND);
		animationStand->SetFrame(0, 0);
		vx = 0;
		break;
	}
	}
}

void Bat::Attack()
{
	switch (state)
	{
	case ATTACKING:
	{
		vx += 0.02f;
		vy += 0.01f;		

		x = x + 2 * cos(2 * 3.14 + vx);
		y = y + 0.5 * sin(2 * 3.14 + vy);

		break;
	}
	case PREPARING:
	{
		if (currentAnimation->isActionFinish())
		{
			SetState(ATTACKING);
			SetAnimation(ANI_ATTACK);
		}
		break;
	}
	default:
	{
		SetState(PREPARING);
		SetAnimation(ANI_STAND);
		animationStand->SetFrame(1, 3);
		/*vx += 0.02f;
		vy += 0.05f;*/
		break;
	}
	}
}

void Bat::Die()
{
	switch (state)
	{
	case DIE:
	{
		if (currentAnimation->isActionFinish())
		{
			vy = 0;
			isDead = true;
			//Aladdin::GetInstance()->score += 50;
		}
		break;
	}
	case DIEBYAPPLE:
	{
		SetState(DIE);
		SetAnimation(ANI_DIE_BY_APPLE);
		isDie = true;
		vy = 0.1f;
		break;
	}
	default:
	{
		Enemy::Die();
		break;
	}
	}
}

void Bat::ChangeFrameSize(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		xDraw -= 250;
		yDraw -= 250;
		w += 500;		
		h += 500;
	}
}

void Bat::ResetFrameSize(GameObject * obj)
{
	if (obj->collType == CollAladdin)
	{
		xDraw += 250;
		yDraw += 250;
		w -= 500;
		h -= 500;
	}
}

void Bat::OnIntersect(GameObject * obj)
{
	if (obj->collType == CollApple)
	{
		SetState(DIEBYAPPLE);
		Die();
		return;
	}
	if (obj->collType == CollAladdin)
	{
		if (Aladdin::GetInstance()->GetState() == Aladdin::CUTTING)
		{
			if (((obj->Right() > this->Left() && obj->x < this->x) || (obj->Left() < this->Right() && obj->x > this->x)) && (obj->Top() < this->Bottom() && obj->Bottom() > this->Top()))
				Die();
			return;
		}
		
		if (this->xInit - 120 <= obj->x && obj->x <= this->xInit + 120 && this->yInit + h + 95 >= obj->Top())
			Attack();
		else if (state == ATTACKING && (this->xInit - 200 >= obj->x || obj->x >= this->xInit + 200))
		{
			Stand();
			x = xInit + 3;
			y = yInit + 16;
		}
	}
}

Bat::~Bat()
{
}
