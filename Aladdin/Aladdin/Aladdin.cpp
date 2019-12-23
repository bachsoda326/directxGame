#include "Aladdin.h"
#include <ctime>
#include "debug.h"
#include "Textures.h"
#include "Apple.h"
#include "NormalGuard.h"
#include "ThinGuard.h"
#include "Bat.h"
#include "Ground.h"
#include "StoneBrick.h"
#include "Chains.h"
#include "SceneManager.h"
#include "BossScene.h"
#include "Abu.h"

Aladdin * Aladdin::__instance = NULL;

Aladdin::Aladdin()
{
	x = ALADDIN_POTISION_X;
	y = ALADDIN_POTISION_Y;
	w = 37;
	h = 50;
	xDraw = x - 18;
	yDraw = y - 50;
	xInit = ALADDIN_POTISION_X_INIT;
	yInit = ALADDIN_POTISION_Y_INIT;
	nx = 0;
	ny = 0;
	isDead = false;
	isDie = false;
	direction = true;
	isAppleCreated = false;
	currentAnimation = new Animation(100);
	isBlink = 0;
	blood = ALADDIN_BLOOD;
	score = ALADDIN_SCORE;
	numApples = ALADDIN_APPLE;
	numRubies = ALADDIN_RUBY;
	numLifes = ALADDIN_BLOOD;
	lastState = STANDING;
	state = STANDING;
	collType = CollAladdin;
	objType = OBJAladdin;
}

Aladdin * Aladdin::GetInstance()
{
	if (__instance == NULL) __instance = new Aladdin();
	return __instance;
}

void Aladdin::LoadResources()
{
	LPDIRECT3DTEXTURE9 texAladdin = Textures::GetInstance()->Get(ID_TEX_ALADDIN);
	// khởi tạo các animation
	animationWait_1 = new Animation("Wait_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 300);
	animationWait_2 = new Animation("Wait_2", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationWait_3 = new Animation("Wait_3", XML_ALADDIN_ANIMATION_PATH, texAladdin, 90);
	animationWait_Swinging = new Animation("Wait_Swinging", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationStand_1 = new Animation("Stand_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationLookUp_1 = new Animation("LookUp_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 45);
	animationRun_1 = new Animation("Run_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 80);
	animationLand_1 = new Animation("Land_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationDuck_1 = new Animation("Duck_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 35);
	animationJump_Standing = new Animation("Jump_Standing", XML_ALADDIN_ANIMATION_PATH, texAladdin, 90);
	animationJump_Running = new Animation("Jump_Running", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationJump_Climbing = new Animation("Jump_Climbing", XML_ALADDIN_ANIMATION_PATH, texAladdin, 50);
	animationClimb_1 = new Animation("Climb_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationCut_Standing = new Animation("Cut_Standing", XML_ALADDIN_ANIMATION_PATH, texAladdin, 85);
	animationCut_LookingUp = new Animation("Cut_LookingUp", XML_ALADDIN_ANIMATION_PATH, texAladdin, 80);
	animationCut_Ducking = new Animation("Cut_Ducking", XML_ALADDIN_ANIMATION_PATH, texAladdin, 65);
	animationCut_Jumping = new Animation("Cut_Jumping", XML_ALADDIN_ANIMATION_PATH, texAladdin, 80);
	animationCut_Climbing = new Animation("Cut_Climbing", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationThrow_Standing = new Animation("Throw_Standing", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationThrow_Ducking = new Animation("Throw_Ducking", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationThrow_Jumping = new Animation("Throw_Jumping", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationThrow_Climbing = new Animation("Throw_Climbing", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationBrake_1 = new Animation("Brake_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 60);
	animationPush = new Animation("Push", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationHurt = new Animation("Hurt", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationDie = new Animation("Die", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationRunNext = new Animation("RunNext", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationEndFly = new Animation("EndFly", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationEndHug = new Animation("EndHug", XML_ALADDIN_ANIMATION_PATH, texAladdin, 250);
	animationRespawn = new Animation("Respawn", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	// animation ban đầu
	currentAnimation = animationJump_Standing;
	standingTime = GetTickCount();

	nx = 0;
	ny = 0;
	isBlink = 0;
	isDead = false;
	isDie = false;
	direction = true;
	isAppleCreated = false;
}

void Aladdin::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//DebugOut("[state] state: %d\n", state);
	//DebugOut(L"[CP] x: %f\n", nx);

	// update v.trí di chuyển vs v.tốc hiện tại
	GameObject::Update(dt);	
	x += dx;
	y += dy;	
	/*vy += 0.018f;*/

	// khi c.bị chết thì chết
	if (state == DIE || isDie)
	{
		Die();
		return;
	}
	// update action theo tr.thái hiện tại
	switch (state)
	{
	case RESETPOSITION:
		ResetPosition();
		return;
	case FLY:
		Fly();
		return;
	case HUG:
		Hug();
		return;
	case RUNNEXT:
		RunNextScene();
		return;
	}

	// đặt khoảng thời gian k thể bị thương
	if (isBlink != 0)
	{
		// sau t giây thì có thể bị thương
		DWORD endBlink = GetTickCount();
		if (endBlink - startBlink > ALADDIN_TIME_BLINK)
		{
			isBlink = 0;
			if (state == HURT)
				state = lastState;
		}
	}

	// xử lý bàn phím và di chuyển
	HandleKeyBoard();
	// k cho Aladdin đi ra khỏi 2 biên map
	if (this->Left() <= MAP_EDGE_LEFT && vx < 0 || this->Right() > MAP_EDGE_RIGHT && vx > 0)
		vx = 0;	
	// v.tốc rơi
	vy += ALADDIN_SPEED_FALL;

	for (int i = 0; i < listApples.size(); i++)
	{
		listApples[i]->Update(dt);
	}
	
	// tăng 1 mạng nếu đc 1000 điểm rồi reset score
	if (score >= 1000)
	{
		numLifes++;
		score -= 1000;
	}
}

void Aladdin::Render()
{	
	D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
	currentAnimation->Render(x, y, xDraw, yDraw, w, h, direction, trans, isBlink);

	for (int i = 0; i < listApples.size(); i++)
	{
		listApples[i]->Render();
	}

	//RenderBoundingBox();
}

void Aladdin::SetAnimation(AladdinAnimations ani)
{
	switch (ani)
	{
	case ANI_WAIT_1:
	{
		//reset frame when press event
		currentAnimation = animationWait_1;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_WAIT_2:
	{
		currentAnimation = animationWait_2;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_WAIT_3:
	{
		currentAnimation = animationWait_3;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_WAIT_SWINGING:
	{
		currentAnimation = animationWait_Swinging;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_STAND_1:
	{
		currentAnimation = animationStand_1;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_LOOKUP_1:
	{
		currentAnimation = animationLookUp_1;
		break;
	}
	case ANI_RUN_1:
	{
		currentAnimation = animationRun_1;
		break;
	}
	case ANI_LAND_1:
	{
		currentAnimation = animationLand_1;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_DUCK_1:
	{
		currentAnimation = animationDuck_1;
		break;
	}
	case ANI_JUMP_STANDING:
	{
		currentAnimation = animationJump_Standing;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_JUMP_RUNNING:
	{
		currentAnimation = animationJump_Running;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_JUMP_CLIMBING:
	{
		currentAnimation = animationJump_Climbing;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_CLIMB_1:
	{
		currentAnimation = animationClimb_1;
		//currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_STANDING:
	{
		currentAnimation = animationCut_Standing;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_LOOKINGUP:
	{
		currentAnimation = animationCut_LookingUp;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_DUCKING:
	{
		currentAnimation = animationCut_Ducking;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_JUMPING:
	{
		currentAnimation = animationCut_Jumping;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_CUT_CLIMBING:
	{
		currentAnimation = animationCut_Climbing;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_THROW_STANDING:
	{
		currentAnimation = animationThrow_Standing;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_THROW_DUCKING:
	{
		currentAnimation = animationThrow_Ducking;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_THROW_JUMPING:
	{
		currentAnimation = animationThrow_Jumping;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_THROW_CLIMBING:
	{
		currentAnimation = animationThrow_Climbing;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_BRAKE_1:
	{
		currentAnimation = animationBrake_1;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_PUSH:
	{
		currentAnimation = animationPush;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_HURT:
	{
		currentAnimation = animationHurt;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_RESPAWN:
	{
		currentAnimation = animationRespawn;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_DIE:
	{
		currentAnimation = animationDie;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_RUNNEXT:
	{
		currentAnimation = animationRunNext;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_FLY:
	{
		currentAnimation = animationEndFly;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_HUG:
	{		
		currentAnimation = animationEndHug;
		currentAnimation->ResetFrame();
		break;
	}
	}
}

void Aladdin::UpdateKey()
{
	if (!keyBoard->KeyDown(DIK_Z))
		keyUp[0] = true;
	if (!keyBoard->KeyDown(DIK_X))
		keyUp[1] = true;
	if (!keyBoard->KeyDown(DIK_C))
		keyUp[2] = true;
	// set các phím
	KeyZ = keyBoard->KeyDown(DIK_Z);
	KeyX = keyBoard->KeyDown(DIK_X);
	KeyC = keyBoard->KeyDown(DIK_C);
	KeyLeft = keyBoard->KeyDown(DIK_LEFT);
	KeyRight = keyBoard->KeyDown(DIK_RIGHT);
	KeyUp = keyBoard->KeyDown(DIK_UP);
	KeyDown = keyBoard->KeyDown(DIK_DOWN);	
}

void Aladdin::HandleKeyBoard()
{
	UpdateKey();
	bool isKeyDown = false;
	// nhấn Z chém
	if (KeyZ && keyUp[0])
	{		
		Cut();
		isKeyDown = true;		
	}
	// nhấn X ném táo
	if (KeyX && keyUp[1] && numApples > 0)
	{
		Throw();
		isKeyDown = true;
	}
	// nhấn C nhảy
	if (KeyC && keyUp[2])
	{
		Jump();
		isKeyDown = true;

	}
	// mũi tên trái phải chạy
	if (KeyLeft || KeyRight)
	{		
		if (ny == -1.0f && vy >= 0)		// khi trên mặt đất
		{
			if (!(nx != 0 && vx == 0))	// khi k va chạm đứng lại theo chiều ngang
			{
				if (state != JUMPING && state != DUCKING && state != LOOK_UP)
				{
					Run();
					isKeyDown = true;
				}
			}
			else if (ny == -1.0f)
			{
				Push();
				isKeyDown = true;
			}
				
		}		

		// set hướng quay của Aladdin 
		switch (state)
		{			
		case JUMPING: case RUNNING: case RUN_LONG_ENOUGH:
		case LOOK_UP: case DUCKING: case STANDING:
		{
			if (KeyRight)
				direction = true;
			else if (KeyLeft)
				direction = false;
			break;
		}
		case CLIMB: case CLIMBING: case FALL:
		{
			if (KeyLeft)
				direction = true;
			else if (KeyRight)
				direction = false;
			break;
		}
		case CUTTING: case THROWING:
		{
			if (lastState == CLIMB || lastState == FALL)
			{
				if (KeyLeft)
					direction = true;
				else if (KeyRight)
					direction = false;
			}
			else
			{
				if (KeyRight)
					direction = true;
				else if (KeyLeft)
					direction = false;
			}
			break;
		}
		}		

		// set vận tốc của Aladdin
		switch (state)
		{
		case JUMPING: case RUNNING: case RUN_LONG_ENOUGH:
		{
			if (KeyRight)
			{
				if (currentAnimation == animationJump_Standing)
					vx = ALADDIN_SPEED_WHENJUMP;
				else
					vx = ALADDIN_SPEED_RUN;
			}
			else if (KeyLeft)
			{
				if (currentAnimation == animationJump_Standing)
					vx = -ALADDIN_SPEED_WHENJUMP;
				else
					vx = -ALADDIN_SPEED_RUN;
			}
			break;
		}
		case CUTTING: case THROWING:
		{
			if (lastState == CLIMB) 
				break;
			if (KeyRight)
			{
				if (currentAnimation == animationJump_Standing)
					vx = ALADDIN_SPEED_WHENJUMP;
				else
					vx = ALADDIN_SPEED_RUN;
			}
			else if (KeyLeft)
			{
				if (currentAnimation == animationJump_Standing)
					vx = -ALADDIN_SPEED_WHENJUMP;
				else
					vx = -ALADDIN_SPEED_RUN;
			}
			break;
		}
		}
	}	
	// mũi tên lên nhìn lên
	if (KeyUp)
	{
		switch (state)
		{
		case STANDING: case RUNNING: case RUN_LONG_ENOUGH: case LOOK_UP:
		case WAITING_1: case WAITING_2:
		{
			LookUp();
			isKeyDown = true;
			break;
		}
		}		
	}
	// mũi tên xuống cúi xuống
	if (KeyDown)
	{
		switch (state)
		{
		case STANDING: case RUNNING: case RUN_LONG_ENOUGH: case DUCKING:
		case WAITING_1: case WAITING_2:
		{
			Duck();
			isKeyDown = true;
			break;
		}
		}		
	}

	// sự kiện xử lý khi thả phím
	if (isKeyDown == false)
	{
		switch (state)
		{
		case HURT:
			Hurt();
			break;
		case RUN_LONG_ENOUGH: case BRAKING:
		{
			if (nx == 0 && vx != 0 && ny == -1.0f && vy == 0)		// khi chạy mà k có va chạm theo phương ngang
			{
				Brake();
			}
			else
			{
				if (ny == 0)		// khi k va chạm theo chiều dọc
				{
					SetState(FALL);
					Jump();
				}
				else
					Stand();
			}			
			break;
		}
		case JUMPING:
		{
			Jump();

			break;
		}
		case CUTTING:
		{
			Cut();
			break;
		}
		case THROWING:
		{
			Throw();
			break;
		}
		case FALLCLIMB: case FALL:
			break;
		case CLIMB: case CLIMBING:			
			break;
		case WAITING_1: case WAITING_2: case WAITING_3:
			Wait();
			break;
		default:
		{
			if (nx == 0 && ny == 0)		// khi k ca chạm theo chiều ngang và dọc
			{				
				SetState(FALL);
				Jump();
			}
			else
			{
				// reset frame animation chạy
				if (currentAnimation == animationRun_1)
					currentAnimation->ResetFrame();
				Stand();
			}			
			break;
		}
		}
	}	
}

void Aladdin::Stand()
{
	switch (state)
	{
	case STANDING:
	{
		/*if (!currentAnimation->isActionFinish())
			break;
		else
		{
			lastState = STANDING;
			SetState(STANDING);
			SetAnimation(ANI_STAND_1);
			vx = 0;
			standingTime = GetTickCount();
		}*/

		Wait();
		break;
	}
	default:
	{		
		if (state == PUSHING)
		{
			if (direction == true)
				x = x - w / 2;
			else
				x = x + w / 2;
		}

		SetState(STANDING);
		SetAnimation(ANI_STAND_1);
		lastState = STANDING;
		//currentAnimation = animationStand_1;
		vx = 0;
		standingTime = GetTickCount();
		break;
	}
	}
}

void Aladdin::Wait()
{
	DWORD startWait = GetTickCount();
	int i = currentAnimation->GetCurrentFrame();
	switch (state)
	{
	case STANDING:
	{
		// sau t giây sẽ chuyển animation sang Wait_1
		if (startWait - standingTime > 2000)
		{
			lastState = state;
			SetState(WAITING_1);
			SetAnimation(ANI_WAIT_1);
			animationWait_1->SetFrame(0, 3);
			standingTime = GetTickCount();
			countWait_1 = 0;
		}

		break;
	}
	case WAITING_1:
	{
		if (currentAnimation == animationWait_1 && currentAnimation->GetLastFrame() == 3 && currentAnimation->isActionFinish())
		{
			animationWait_1->SetFrame(3, 1);
			countWait_1++;
		}
		if (currentAnimation == animationWait_1 && currentAnimation->GetLastFrame() == 1 && currentAnimation->isActionFinish())
		{
			animationWait_1->SetFrame(4, 6);
			countWait_1++;
		}
		if (currentAnimation == animationWait_1 && currentAnimation->GetLastFrame() == 6 && currentAnimation->isActionFinish())
		{
			animationWait_1->SetFrame(6, 4);
			countWait_1++;
		}
		if (currentAnimation == animationWait_1 && currentAnimation->GetLastFrame() == 4 && currentAnimation->isActionFinish())
		{
			animationWait_1->SetFrame(1, 3);
			countWait_1++;
		}
		if (countWait_1 == 6)
		{
			SetState(WAITING_2);
			SetAnimation(ANI_WAIT_2);
		}

		break;
	}
	case WAITING_2:
	{
		if (currentAnimation->isActionFinish())
		{
			SetState(WAITING_3);
			SetAnimation(ANI_WAIT_3);
		}
		break;
	}
	case WAITING_3:
	{
		break;
	}	
	}
}

void Aladdin::Duck()
{
	switch (state)
	{	
	case DUCKING: case CUTTING: case THROWING:
	{
		lastState = DUCKING;
		SetState(DUCKING);
		SetAnimation(ANI_DUCK_1);
		vx = 0;

		int i = currentAnimation->GetCurrentFrame();
		if (i == 3)
			animationDuck_1->SetFrame(3, 3);

		if (ny == 0)
		{
			state = FALL;
			Jump();
		}
		break;
	}
	case STANDING: case RUNNING: case RUN_LONG_ENOUGH:
	case WAITING_1: case WAITING_2:
	{
		SetState(DUCKING);
		SetAnimation(ANI_DUCK_1);		
		animationDuck_1->SetFrame(0, 3);
		vx = 0;
		break;
	}
	}
}

void Aladdin::LookUp()
{
	switch (state)
	{	
	case LOOK_UP: case CUTTING:
	{
		lastState = LOOK_UP;
		SetState(LOOK_UP);
		SetAnimation(ANI_LOOKUP_1);
		vx = 0;

		int i = currentAnimation->GetCurrentFrame();
		if (i == 2)
			animationLookUp_1->SetFrame(2, 2);

		if (ny == 0)
		{
			state = FALL;
			Jump();
		}
		break;
	}
	case STANDING: case RUNNING: case RUN_LONG_ENOUGH:
	case WAITING_1: case WAITING_2:
	{
		lastState = STANDING;
		SetState(LOOK_UP);
		SetAnimation(ANI_LOOKUP_1);		
		animationLookUp_1->SetFrame(0, 2);
		vx = 0;
		break;
	}
	}
}

void Aladdin::Run()
{	
	switch (state)
	{
	case RUNNING:
	{
		int i = currentAnimation->GetCurrentFrame();
		if (i == 1)
			animationRun_1->SetFrame(2, 12);
		if (currentAnimation == animationRun_1 && i == 7)
			SetState(RUN_LONG_ENOUGH);
		break;
	}
	case RUN_LONG_ENOUGH:
		break;
	case JUMPING:
	{
		SetState(RUNNING);
		SetAnimation(ANI_RUN_1);
		animationRun_1->SetFrame(2, 12);
		//currentAnimation->SetCurrentFrame(7);
		break;
	}
	default:
	{
		SetState(RUNNING);
		SetAnimation(ANI_RUN_1);
		animationRun_1->SetFrame(0, 12);
		break;
	}
	}
}

void Aladdin::Brake()
{
	switch (state)
	{
	case RUN_LONG_ENOUGH:
	{
		SetState(BRAKING);
		SetAnimation(ANI_BRAKE_1);
		if (vx > 0)
			vx = ALADDIN_SPEED_BRAKE;
		else
			vx = -ALADDIN_SPEED_BRAKE;
		break;
	}
	default:
	{		
		if (currentAnimation->isActionFinish())
			Stand();
		break;
	}
	}
}

void Aladdin::Push()
{	
	switch (state)
	{
	case PUSHING:
	{		
		if (direction == true)
		{
			if (KeyLeft)
			{
				Stand();
				break;
			}
			vx = ALADDIN_SPEED_RUN;
		}
		else
		{
			if (KeyRight)
			{
				Stand();
				break;
			}
			vx = -ALADDIN_SPEED_RUN;
		}
		if (currentAnimation->GetFirstFrame() == 0)
			animationPush->SetFrame(1, 8);
		break;
	}
	default:
	{
		SetState(PUSHING);
		if (direction == true)
		{
			x = xDraw + w;
			vx = ALADDIN_SPEED_RUN;
		}
		else
		{
			x = xDraw;
			vx = -ALADDIN_SPEED_RUN;
		}
		SetAnimation(ANI_PUSH);
		break;
	}
	}
}

void Aladdin::Jump()
{
	switch (state)
	{
	case RUNNING: case RUN_LONG_ENOUGH:
	{
		SetState(JUMPING);
		SetAnimation(ANI_JUMP_RUNNING);
		vy -= ALADDIN_SPEED_JUMPRUN;

		keyUp[2] = false;
		break;

	}
	case CLIMB: case CLIMBING:
	{
		lastState = state;
		SetState(JUMPING);				
		SetAnimation(ANI_JUMP_CLIMBING);
		vy -= ALADDIN_SPEED_JUMPCLIMB;

		keyUp[2] = false;
		break;
	}
	case FALL: case WAITING_3:
	{
		lastState = STANDING;
		SetState(JUMPING);				
		SetAnimation(ANI_JUMP_STANDING);
		animationJump_Standing->SetFrame(3, 9);
		//vy -= 0.05f;
		//y += 30;

		keyUp[2] = false;
		break;
	}
	case FALLCLIMB:
	{
		lastState = STANDING;
		SetState(JUMPING);				
		SetAnimation(ANI_JUMP_STANDING);
		animationJump_Standing->SetFrame(3, 9);
		// làm cho Aladdin rời khỏi dây khi trèo xuống hết dây
		vy -= 0.05f;
		y += h;

		keyUp[2] = false;
		break;
	}
	case CUTTING: case THROWING:
	{		
		if (lastState == FALL || lastState == CLIMB)
		{
			state = lastState;
			Jump();
			break;
		}

		state = JUMPING;
		SetAnimation(ANI_JUMP_RUNNING);
		animationJump_Running->SetCurrentFrame(5);

		keyUp[2] = false;
		break;
	}
	case JUMPING:
	{
		int i = currentAnimation->GetCurrentFrame();
		if (currentAnimation == animationJump_Climbing && i == 8)
		{
			//y += 37;
			SetAnimation(ANI_JUMP_STANDING);
			animationJump_Standing->SetFrame(3, 9);			
		}

		if (ny == -1.0f && vy == 0)		// khi trên mặt đất
		{
			currentAnimation->ResetFrame();
			if (KeyRight || KeyLeft)
				Run();
			else
				Stand();
		}
		break;
	}
	default:
	{
		if (state == PUSHING)
		{
			if (direction == true)
				x = x - w / 2;
			else
				x = x + w / 2;
		}

		lastState = state;
		SetState(JUMPING);
		SetAnimation(ANI_JUMP_STANDING);
		animationJump_Standing->SetFrame(0, 9);
		vy -= ALADDIN_SPEED_JUMP;

		keyUp[2] = false;
		break;
	}
	}
}

void Aladdin::Climb()
{	
	switch (state)
	{
	case JUMPING:
	{		
		if ((lastState != CLIMB && lastState != CLIMBING) || (lastState == CLIMB && vy > 0.22f) || (lastState == CLIMBING && vy > 0.22f))
		{
			SetState(CLIMB);			
			SetAnimation(ANI_CLIMB_1);
			animationClimb_1->SetFrame(0, 0);
			vx = 0;
			vy = 0;
		}
		break;
	}
	case CLIMB:
	{
		if (KeyUp)
		{
			lastState = state;
			SetState(CLIMBING);			
			animationClimb_1->SetFrame(0, 9);
			vx = 0;
			vy = -ALADDIN_SPEED_CLIMB;
		}
		else if (KeyDown)
		{
			lastState = state;
			SetState(CLIMBING);			
			animationClimb_1->SetFrame(9, 0);
			vx = 0;
			vy = ALADDIN_SPEED_CLIMB;
		}
		break;
	}
	case CLIMBING:
	{
		if (KeyUp)
		{
			vx = 0;
			vy = -ALADDIN_SPEED_CLIMB;
		}
		else if (KeyDown)
		{
			vx = 0;
			vy = ALADDIN_SPEED_CLIMB;
		}
		else
		{
			lastState = state;
			state = CLIMB;
			vx = 0;
			vy = 0;
			int i = currentAnimation->GetCurrentFrame();
			animationClimb_1->SetFrame(i, i);
		}
		break;
	}
	case CUTTING: case THROWING:
	{
		if (currentAnimation->isActionFinish())
		{
			SetState(CLIMB);			
			SetAnimation(ANI_CLIMB_1);
			vx = 0;
			vy = 0;			
		}
		break;
	}
	}
}

void Aladdin::Cut()
{
	switch (state)
	{	
	case RUNNING: case RUN_LONG_ENOUGH: case CLIMBING: case PUSHING:
		break;	
	case LOOK_UP:
	{
		lastState = state;
		SetState(CUTTING);
		SetAnimation(ANI_CUT_LOOKINGUP);
		animationCut_LookingUp->SetFrame(0, 11);
		vx = 0;	

		keyUp[0] = false;
		break;
	}
	case DUCKING:
	{
		lastState = DUCKING;
		SetState(CUTTING);
		SetAnimation(ANI_CUT_DUCKING);
		vx = 0;

		keyUp[0] = false;
		break;
	}
	case JUMPING:
	{
		lastState = JUMPING;
		SetState(CUTTING);
		SetAnimation(ANI_CUT_JUMPING);
		
		keyUp[0] = false;
		break;
	}
	case CLIMB: case FALL:
	{		
		lastState = state;
		SetState(CUTTING);		
		SetAnimation(ANI_CUT_CLIMBING);
		vy = 0;
		// t.đổi y để animation lúc chém trùng vs lúc trèo
		if (lastState == CLIMB)
			y -= 25;

		keyUp[0] = false;
		break;
	}
	case CUTTING:
	{
		int i = currentAnimation->GetCurrentFrame();
		// lặp lại chém khi nhìn lên nhiều lần
		if (currentAnimation == animationCut_LookingUp && animationCut_LookingUp->GetFirstFrame() == 0 && i == 10)
			animationCut_LookingUp->SetFrame(2, 9);		
		
		if (currentAnimation->isActionFinish())
		{
			GameSound::getInstance()->play(ALADDIN_CUT_MUSIC);

			switch (lastState)
			{			
			case DUCKING:
			{
				if (KeyDown)
					Duck();
				else
				{
					SetState(DUCKING);
					Stand();
				}
				break;
			}
			case LOOK_UP:
			{
				/*if (i == 2 && animationCut_LookingUp->GetLastFrame() == 9)
					animationCut_LookingUp->SetFrame(2, 11);
				else*/
				{					
					Stand();
				}
				break;
			}	
			case CLIMB:
			{	
				// t.đổi y lại như cũ khi chém xong
				y += 25;
				Climb();
				break;
			}			
			default:
			{				
				if (ny == 0.0f || (ny == -1.0f && vy != 0))		// đang rơi hoặc gần rơi xuống đất
					Jump();
				else
					Stand();
				break;
			}
			}			
		}
		if (lastState == JUMPING && vy == 0 && ny == -1.0f)		// đang trên mặt đất sau khi nhảy xong
		{
			Stand();
		}		
		break;
	}
	default:
	{
		if (lastState == DUCKING && state != STANDING || lastState == FALL || lastState == CLIMB)
		{
			state = lastState;
			Cut();
			break;
		}

		if (lastState == DUCKING && lastState == STANDING)
			lastState = STANDING;

		if (!(ny == -1.0f && vy == 0))		// đang k trên mặt đất
		{			
			SetState(JUMPING);
			Cut();
			break;
		}
		
		SetState(CUTTING);
		SetAnimation(ANI_CUT_STANDING);		
		vx = 0;

		keyUp[0] = false;
		break;
	}		
	}	
}

void Aladdin::Throw()
{
	switch (state)
	{
	case RUNNING: case RUN_LONG_ENOUGH: case CLIMBING: case PUSHING:
		break;	
	case DUCKING:
	{
		lastState = DUCKING;
		SetState(THROWING);
		SetAnimation(ANI_THROW_DUCKING);
		vx = 0;

		isAppleCreated = false;
		keyUp[1] = false;
		break;
	}
	case JUMPING:
	{
		lastState = JUMPING;
		SetState(THROWING);
		SetAnimation(ANI_THROW_JUMPING);

		isAppleCreated = false;
		keyUp[1] = false;
		break;
	}
	case CLIMB: case FALL:
	{
		lastState = state;
		SetState(THROWING);		
		SetAnimation(ANI_THROW_CLIMBING);
		vy = 0;
		// t.đổi y để animation lúc ném trùng vs lúc trèo
		if (lastState == CLIMB)
			y -= 25;

		isAppleCreated = false;
		keyUp[1] = false;
		break;
	}
	case THROWING:
	{
		int i = currentAnimation->GetCurrentFrame();
		// tạo táo khi animation ném đến đc frame thứ 3
		if ((currentAnimation == animationThrow_Standing && i == 3 || currentAnimation == animationThrow_Ducking && i == 3 || currentAnimation == animationThrow_Jumping && i == 3 || currentAnimation == animationThrow_Climbing && i == 4) && isAppleCreated == false)
		{
			GameSound::getInstance()->play(THROW_MUSIC);

			CreateApple();
			isAppleCreated = true;
		}

		if (currentAnimation->isActionFinish())
		{			
			switch (lastState)
			{
			case DUCKING:
			{
				if (KeyDown)
					Duck();
				else
				{
					SetState(DUCKING);
					Stand();
				}
				break;
			}
			case CLIMB:
				// t.đổi y như cũ lúc ném xong
				y += 20;
				Climb();
				break;
			default:
			{				
				if (ny == 0)		// đang k trên mặt đất
					Jump();
				else
					Stand();
				break;
			}
			}
		}
		if (lastState == JUMPING && vy == 0 && ny == -1.0f)		// đang trên mặt đất sau khi nhảy xong
		{
			Stand();
		}

		/*if (ny == 0 && lastState != JUMPING)
		{
			state = FALL;
			Jump();
		}*/
		break;
	}
	default:
	{
		if (lastState == DUCKING && state != STANDING || lastState == CLIMB || lastState == FALL)
		{
			if (lastState == CLIMB)
				y += 20;
			state = lastState;
			Throw();
			break;
		}

		if (lastState == DUCKING && lastState == STANDING)
			lastState = STANDING;

		if (ny == 0.0f || (ny == -1.0f && vy != 0))		// đang rơi hoặc gần rơi xuống đất
		{
			SetState(JUMPING);
			Throw();
			break;
		}

		SetState(THROWING);
		SetAnimation(ANI_THROW_STANDING);
		vx = 0;
		keyUp[1] = false;
		isAppleCreated = false;

		break;
	}
	}
}

void Aladdin::Hurt()
{
	switch (state)
	{
	case HURT:
	{
		break;
	}
	default:
	{
		GameSound::getInstance()->play(ALADDIN_HURT_MUSIC);

		if ((state == STANDING || state == WAITING_1 || state == WAITING_2))
		{
			SetState(HURT);
			SetAnimation(ANI_HURT);
			vx = 0;
		}
		isBlink = 1;
		startBlink = GetTickCount();
		blood -= ALADDIN_HURT;

		if (blood <= 0)
			Die();
		break;
	}
	}
}

void Aladdin::Die()
{
	switch (state)
	{
	case DIE:
	{
		if (currentAnimation->isActionFinish())
		{
			Abu::GetInstance()->isDead = true;
			if (numLifes == 0)
				isDead = true;
			else
				ResetPosition();
		}
		//isBlink = 0;
		break;
	}
	default:
	{
		SetState(DIE);
		SetAnimation(ANI_DIE);
		isDie = true;
		direction = true;
		numLifes--;
		vy = 0;
		vx = 0;
		isBlink = 0;
		Abu::GetInstance()->SetPosition(x + ABU_POTISION_ALADDINDIE_X, y + ABU_POTISION_ALADDINDIE_Y);
		Abu::GetInstance()->isDead = false;
		// Khỉ Abu quạt
		Abu::GetInstance()->beginStat = 1;
		Abu::GetInstance()->LoadResources();
		break;
	}
	}
}

void Aladdin::RunNextScene()
{
	switch (state)
	{
	case RUNNEXT:
	{		
		break;
	}
	default:
	{
		vx = -ALADDIN_SPEED_RUNNEXT;
		vy = 0;
		SetState(RUNNEXT);
		SetAnimation(ANI_RUNNEXT);
		isBlink = 0;
		break;
	}
	}
}

void Aladdin::Fly()
{
	switch (state)
	{
	case FLY:
	{		
		break;
	}
	default:
	{
		vx = ALADDIN_SPEED_FLY_VX;
		vy = -ALADDIN_SPEED_FLY_VY;
		SetState(FLY);
		SetAnimation(ANI_FLY);
		isBlink = 0;
		break;
	}
	}
}

void Aladdin::Hug()
{
	switch (state)
	{
	case HUG:
	{
		if (currentAnimation->GetCurrentFrame() == 9)
		{
			animationEndHug->SetFrame(9, 9);
		}
		break;
	}
	default:
	{
		vx = 0;
		vy = 0;
		SetState(HUG);
		SetAnimation(ANI_HUG);
		isBlink = 0;
		break;
	}
	}
}

void Aladdin::ResetPosition()
{
	switch (state)
	{
	case RESETPOSITION:
	{
		if (currentAnimation->isActionFinish())
		{
			y -= 20;
			Stand();
		}
		break;
	}
	default:
	{
		GameSound::getInstance()->play(COMEIN_MUSIC);

		SetAnimation(ANI_RESPAWN);
		SetState(RESETPOSITION);		
		isBlink = 1;
		xDraw = xInit;
		yDraw = yInit;
		x = xDraw + 6;
		y = yDraw + 33;

		isDie = false;
		blood = ALADDIN_BLOOD;
		break;
	}
	}
}

vector<GameObject*>* Aladdin::GetList()
{
	return &listApples;
}

void Aladdin::CreateApple()
{
	// trừ số táo của Aladdin lúc tạo táo khi ném
	numApples--;
	GameObject* apple = new Apple();	

	if (lastState == FALL || lastState == CLIMB || lastState == CLIMBING)
	{
		apple->yDraw = (this->Top() + this->Bottom()) / 2;
		// vận tốc ném lên (vy), ném ngang (vx) của táo
		apple ->vy = -APPLE_SPEED_THROWCLIMB_VY;
		if (!direction)
		{
			apple->xDraw = this->Right();
			apple->vx = APPLE_SPEED_THROWCLIMB_VX;
		}
		else
		{
			apple->xDraw = this->Left();
			apple->vx = -APPLE_SPEED_THROWCLIMB_VX;
		}
	}
	else
	{
		apple->yDraw = this->Top();
		// vận tốc ném lên (vy), ném ngang (vx) của táo
		apple->vy = -APPLE_SPEED_THROW_VY;
		if (direction)
		{
			apple->xDraw = this->Right();
			apple->vx = APPLE_SPEED_THROW_VX;
		}
		else
		{
			apple->xDraw = this->Left();
			apple->vx = -APPLE_SPEED_THROW_VX;
		}
	}

	apple->direction = this->direction;
	apple->LoadResources();
	listApples.push_back(apple);
}

void Aladdin::DeleteApple(GameObject * apple)
{
	for (int i = 0; i < listApples.size(); i++)
	{
		if (listApples[i] == apple)
		{
			listApples.erase(listApples.begin() + i);
			delete apple;
			apple = 0;
		}
	}
}

void Aladdin::OnCollision(GameObject * obj, float nx, float ny)
{
	switch (obj->collType)
	{
	case CollGround: case CollFence:
		Collision::PreventMove(this, obj, nx, ny);
		break;
	case CollBrick:
	{
		int i = obj->currentAnimation->GetCurrentFrame();
		int j = obj->currentAnimation->GetLastFrame();
		if (j == 0)
		{
			if (i >= 2)
				Collision::PreventMove(this, obj, nx, ny);
		}
		else
		{
			if (i == 3 || i == 4)
				Collision::PreventMove(this, obj, nx, ny);
		}
		break; 
	}	
	}
}

void Aladdin::OnIntersect(GameObject * obj)
{
	if (obj->objType == OBJBallTrap)
	{
		int i = obj->currentAnimation->GetCurrentFrame();
		if (i >= 11)
		{
			if (isBlink == 0)
				Hurt();
		}
	}
	if (obj->objType == OBJSharpTrap)
	{
		int i = obj->currentAnimation->GetCurrentFrame();
		if (i >= 3)
		{
			if (isBlink == 0)
				Hurt();
		}
	}
	if (obj->collType == CollChains)
	{
		// khi trèo xuống hết dây thì Aladdin tự nhảy xuống
		if (y > obj->yDraw + obj->h && KeyDown)
		{
			if (state == CLIMBING)
				SetState(FALLCLIMB);
			Jump();
			return;
		}
		// khi chạm dây Aladdin sẽ chuyển sang trạng thái trèo (CLIMB)
		if (x > obj->xDraw + obj->w / 2 - 5 && x < obj->xDraw + obj->w / 2 + 5 && yDraw > obj->yDraw - 2)
		{
			if (!((lastState == CLIMB || lastState == CLIMBING) && state == JUMPING))
			{
				vy = 0;
				x = obj->xDraw + obj->w / 2;
				if (y > obj->Bottom())
					y = obj->Bottom();
			}
			if (yDraw < obj->yDraw)
				KeyUp = false;
			Climb();
		}
	}

	// va chạm vs enemy
	if (obj->collType == CollEnemy)
	{
		switch (obj->objType)
		{		
		case OBJBoss:
		{
			if (Collision::AABBCheck(this, obj))		// k.tra collision kiểu "Va chạm"
			{
				if (isBlink == 0)
					Hurt();
			}
			break;
		}
		case OBJFire:
		{
			if (this->Bottom() > obj->Top() + 18)
			{
				if (isBlink == 0)
					Hurt();
			}
			break;
		}
		case OBJBat:
		{
			if (obj->GetState() == Bat::ATTACKING)
			{
				if (((obj->Right() > this->Left() && obj->x < this->x) || (obj->Left() < this->Right() && obj->x > this->x)) && (obj->Top() < this->Bottom() && obj->Bottom() > this->Top()))
				{
					if (isBlink == 0 && state != CUTTING)
						Hurt();
				}
			}
			break;
		}
		case OBJBone:
		{
			if (isBlink == 0)
				Hurt();
			break;
		}
		case OBJThinGuard:
		{
			if (obj->GetState() == ThinGuard::CUTTING_1)
			{
				if ((!obj->direction && obj->Right() > this->Left() && obj->x < this->x) || (obj->direction && obj->Left() < this->Right() && obj->x > this->x))
				{
					if (isBlink == 0 && state != CUTTING)
						Hurt();
				}
			}
			break;
		}
		case OBJNormalGuard:
		{
			if (obj->GetState() == NormalGuard::CUTTING_1 || obj->GetState() == NormalGuard::CUTTING_2)
			{
				if ((!obj->direction && obj->Right() > this->Left() && obj->x < this->x) || (obj->direction && obj->Left() < this->Right() && obj->x > this->x))
				{
					if (isBlink == 0 && state != CUTTING)
						Hurt();
				}
			}
			break;
		}
		}
	}

	// cộng điểm cộng máu khi ăn item
	if (obj->collType == CollItem && obj->isActived == false)
	{
		switch (obj->objType)
		{		
		case OBJApple:
			numApples++;
			score += ALADDIN_SCORE_APPLE;
			break;
		case OBJGenieFace:
			score += ALADDIN_SCORE_GENIEFACE;
			GameSound::getInstance()->play(WOW_MUSIC);
			break;
		case OBJGenieJar:
			// vị trí hồi sinh
			xInit = obj->xDraw;
			yInit = obj->yDraw;
			break;
		case OBJBlueHeart:
			score += ALADDIN_SCORE_BLUEHEART;
			blood += ALADDIN_ADD_BLOOD;
			break;
		case OBJRuby:
			score += ALADDIN_SCORE_RUBY;
			numRubies++;
			break;
		}
	}
}