#include "NormalGuard.h"
#include "Textures.h"

NormalGuard::NormalGuard()
{
	isDead = false;
	objType = OBJGuard2;
	currentAnimation = new Animation(100);
	
	w = 30;
	h = 20;
	vx = 0;
	vy = 0;
}

NormalGuard::NormalGuard(float left, float top, float width, float height)
{
	xDraw = left;
	yDraw = top;
	x = xDraw + 24;
	y = yDraw + 59;
	direction = true;
	collType = CollEnemy;
}

void NormalGuard::LoadResources()
{
	LPDIRECT3DTEXTURE9 texGuards = Textures::GetInstance()->Get(ID_TEX_GUARDS);

	animationIdle = new Animation("Idle", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 300);
	animationRun = new Animation("Run", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 300);
	animationRunOnFire = new Animation("RunOnFire", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 100);
	animationCut_1 = new Animation("Cut_1", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 100);
	animationCut_2 = new Animation("Cut_2", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 100);
	animationHurt = new Animation("Hurt", XML_NORMALGUARD_ANIMATION_PATH, texGuards, 100);

	currentAnimation = animationRun;
	vx = -0.03f;
	//animationIdle->SetFrame(0, 0);
}

void NormalGuard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	x += dx;
	y += dy;	
}

void NormalGuard::Render()
{
	if (currentAnimation == animationRun && currentAnimation->isActionFinish())
	{
		SetAnimation(ANI_IDLE);
		vx = 0;
	}
	if (currentAnimation == animationIdle && currentAnimation->isActionFinish())
	{
		SetAnimation(ANI_RUN);
		direction = !direction;
		if (direction)
			vx = -0.03f;
		else vx = 0.03f;
	}

	if (true)
	{
		// // Vector trans giúp dời ảnh theo camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, trans);
	}
	else
		currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, D3DXVECTOR2(0, 0));

	//RenderBoundingBox();
}

void NormalGuard::SetAnimation(NormalGuardAnimations ani)
{
	switch (ani)
	{
	case ANI_IDLE:
	{
		//reset frame when press event
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
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_1:
	{
		currentAnimation = animationCut_1;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_2:
	{
		currentAnimation = animationCut_2;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_HURT:
	{
		currentAnimation = animationHurt;
		//currentAnimation->ResetFrame();
		break;
	}
	}
}

NormalGuard::~NormalGuard()
{
}
