#include "Abu.h"

Abu * Abu::__instance = NULL;

Abu::Abu()
{
	LPDIRECT3DTEXTURE9 texAbu = Textures::GetInstance()->Get(ID_TEX_ABU);
	// khởi tạo các animation
	animationFan = new Animation("Fan", XML_ABU_ANIMATION_PATH, texAbu, 100);
	animationRun = new Animation("Run", XML_ABU_ANIMATION_PATH, texAbu, 100);

	collType = CollUnknown;
	objType = OBJAbu;
}

Abu * Abu::GetInstance()
{
	if (__instance == NULL) __instance = new Abu();
	return __instance;
}

void Abu::LoadResources()
{		
	direction = true;
	isDie = false;
	isDead = false;
	vx = 0;
	vy = 0;

	SetAnimation(ANI_FAN);

	if (beginStat == 0)
	{
		SetState(FAN);
		Run();
	}
	else
	{
		SetState(RUN);
		Fan();
	}
}

void Abu::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// update v.trí di chuyển vs v.tốc hiện tại
	GameObject::Update(dt);
	x += dx;
	y += dy;

	// update action theo tr.thái hiện tại
	switch (state)
	{
	case RUN:
		Run();
		break;
	default:
		Fan();
		break;
	}
}

void Abu::SetAnimation(AbuAnimations ani)
{
	switch (ani)
	{
	case ANI_RUN:
	{		
		currentAnimation = animationRun;
		currentAnimation->ResetFrame();
		break;
	}
	default:
		currentAnimation = animationFan;
		currentAnimation->ResetFrame();
		break;
	}
}

void Abu::Run()
{
	switch (state)
	{
	case RUN:
	{
		break;
	}
	default:
	{
		SetState(RUN);
		SetAnimation(ANI_RUN);
		vx = -ABU_SPEED_RUN;
		vy = 0;
		break;
	}
	}
}

void Abu::Fan()
{
	switch (state)
	{
	case FAN:
	{
		break;
	}
	default:
	{
		SetState(FAN);
		SetAnimation(ANI_FAN);
		vx = 0;
		vy = 0;
		break;
	}
	}
}

Abu::~Abu()
{
}
