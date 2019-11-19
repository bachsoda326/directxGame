#include "Aladdin.h"
#include <ctime>
#include "debug.h"
#include "Textures.h"
#include "Apple.h"

CAladdin * CAladdin::__instance = NULL;

CAladdin::CAladdin()
{
	x = 0;
	y = 0;
	w = 37;
	h = 50;
	xDraw = x - 18;
	yDraw = y - 50;
	last_vy = 0;
	direction = true;
	isAppleCreated == false;
	currentAnimation = new CAnimation(100);
	lastState = STANDING;
	state = STANDING;
}

void CAladdin::LoadResources()
{
	LPDIRECT3DTEXTURE9 texAladdin = CTextures::GetInstance()->Get(ID_TEX_ALADDIN);
	
	animationWait_1 = new CAnimation("Wait_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 300);
	animationWait_2 = new CAnimation("Wait_2", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationWait_3 = new CAnimation("Wait_3", XML_ALADDIN_ANIMATION_PATH, texAladdin, 90);
	animationWait_Swinging = new CAnimation("Wait_Swinging", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationStand_1 = new CAnimation("Stand_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationLookUp_1 = new CAnimation("LookUp_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 45);
	animationRun_1 = new CAnimation("Run_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 85);
	animationLand_1 = new CAnimation("Land_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationDuck_1 = new CAnimation("Duck_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 35);
	animationJump_Standing = new CAnimation("Jump_Standing", XML_ALADDIN_ANIMATION_PATH, texAladdin, 90);
	animationJump_Running = new CAnimation("Jump_Running", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationJump_Swinging = new CAnimation("Jump_Swinging", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationCut_Standing = new CAnimation("Cut_Standing", XML_ALADDIN_ANIMATION_PATH, texAladdin, 85);
	animationCut_LookingUp = new CAnimation("Cut_LookingUp", XML_ALADDIN_ANIMATION_PATH, texAladdin, 80);
	animationCut_Ducking = new CAnimation("Cut_Ducking", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationCut_Jumping = new CAnimation("Cut_Jumping", XML_ALADDIN_ANIMATION_PATH, texAladdin, 80);
	animationCut_Swinging = new CAnimation("Cut_Swinging", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationThrow_Standing = new CAnimation("Throw_Standing", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationThrow_Ducking = new CAnimation("Throw_Ducking", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationThrow_Jumping = new CAnimation("Throw_Jumping", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationThrow_Swinging = new CAnimation("Throw_Swinging", XML_ALADDIN_ANIMATION_PATH, texAladdin, 100);
	animationBrake_1 = new CAnimation("Brake_1", XML_ALADDIN_ANIMATION_PATH, texAladdin, 60);

	currentAnimation = animationJump_Standing;
	standingTime = GetTickCount();
}

//void CAladdin::SetCamera(CCamera * camera)
//{
//	this->camera = camera;
//}

void CAladdin::UpdateKey()
{
	if (!keyBoard->KeyDown(DIK_Z))
		keyUp[0] = true;
	if (!keyBoard->KeyDown(DIK_X))
		keyUp[1] = true;
	if (!keyBoard->KeyDown(DIK_C))
		keyUp[2] = true;
	// setup keyboard
	KeyZ = keyBoard->KeyDown(DIK_Z);
	KeyX = keyBoard->KeyDown(DIK_X);
	KeySpace = keyBoard->KeyDown(DIK_C);
	KeyLeft = keyBoard->KeyDown(DIK_LEFT);
	KeyRight = keyBoard->KeyDown(DIK_RIGHT);
	KeyUp = keyBoard->KeyDown(DIK_UP);
	KeyDown = keyBoard->KeyDown(DIK_DOWN);	
}

void CAladdin::HandleKeyBoard()
{
	UpdateKey();

	bool isKeyDown = false;

	if (KeyZ && keyUp[0])
	{		
		Cut();
		isKeyDown = true;		
	}
	if (KeyX && keyUp[1])
	{
		Throw();
		isKeyDown = true;
	}
	if (KeySpace && keyUp[2])
	{
		Jump();
		isKeyDown = true;

	}
	
	if (KeyLeft || KeyRight)
	{
		// 12:26 13/11
		if (vy >= 0 && y + 20 >= MAP_HEIGHT - 9)
		{
			if (state != JUMPING && state != DUCKING && state != LOOK_UP)
			{
				Run();
				isKeyDown = true;
			}
		}		

		// set hướng quay của Aladdin 
		switch (state)
		{
		case DUCKING: case RUNNING: case RUN_LONG_ENOUGH: case LOOK_UP: case JUMPING:
		{
			if (KeyRight)
				direction = true;
			else if (KeyLeft)
				direction = false;
			else
				break;
		}
		case CUTTING: case THROWING:
		{
			if (lastState == CLIMB || lastState == SWING)
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
		case JUMPING: case RUNNING: case RUN_LONG_ENOUGH: case CUTTING: case THROWING:
		{
			if (KeyRight)
				vx = ALADDIN_SPEED;
			else if (KeyLeft)
				vx = -ALADDIN_SPEED;
			break;
		}		
		}
	}	
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
		case RUN_LONG_ENOUGH: case BRAKING:
		{
			if (/*normalx == 0 && vx != 0 &&*/ vy == 0 && y + 20 >= MAP_HEIGHT - 9)
			{
				Brake();
			}
			else
			{
				if (vy != 0 && y + 20 < MAP_HEIGHT - 9)
				{
					SetState(JUMPING);
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
		case WAITING_1: case WAITING_2: case WAITING_3: case WAITING_SWINGING:
			Wait();
			break;
		default:
		{	
			if (vy != 0 && y + 20 < MAP_HEIGHT - 9)
			{
				SetState(JUMPING);
				Jump();
			}
			else
			{
				// reset frame when click button event
				if (currentAnimation == animationRun_1)
					currentAnimation->ResetFrame();
				Stand();
			}			
			break;
		}
		}
	}
	
}

void CAladdin::Run()
{	
	switch (state)
	{
	case RUNNING:
	{
		int i = currentAnimation->GetCurrentFrame();
		if (i == 1)
			animationRun_1->SetFrame(2, 12);
		if (i == 5)
			SetState(RUN_LONG_ENOUGH);
		break;
	}
	case RUN_LONG_ENOUGH:
		break;
	/*case JUMPING:
	{
		SetState(RUN_LONG_ENOUGH);
		SetAnimation(ANI_RUN_1);
		animationRun_1->SetFrame(2, 12);
		currentAnimation->SetCurrentFrame(7);
		break;
	}*/
	default:
	{
		SetState(RUNNING);
		SetAnimation(ANI_RUN_1);
		animationRun_1->SetFrame(0, 12);

		break;
	}
	}
}

void CAladdin::Brake()
{
	switch (state)
	{
	case RUN_LONG_ENOUGH:
	{
		SetState(BRAKING);
		SetAnimation(ANI_BRAKE_1);
		if (vx > 0)
			vx = 0.05f;
		else
			vx = -0.05f;
		break;
	}
	default:
	{
		//int i = currentAnimation->GetCurrentFrame();
		if (/*i == 150 && */currentAnimation->isActionFinish() == true)
			Stand();
		break;
	}
	}
}

void CAladdin::Duck()
{
	switch (state)
	{
	case STANDING: case RUNNING: case RUN_LONG_ENOUGH:
	case WAITING_1: case WAITING_2:
	{
		SetState(DUCKING);
		SetAnimation(ANI_DUCK_1);
		vx = 0;
		animationDuck_1->SetFrame(0, 3);
		
		break;
	}
	case DUCKING: case CUTTING: case THROWING:
	{
		lastState = DUCKING;
		SetState(DUCKING);
		SetAnimation(ANI_DUCK_1);
		vx = 0;
		
		int i = currentAnimation->GetCurrentFrame();
		
		if(i == 3)
			animationDuck_1->SetFrame(3, 3);
				
		break;
	}
	}
}

void CAladdin::Cut()
{
	switch (state)
	{	
	case RUNNING: case RUN_LONG_ENOUGH: case SWINGING: case CLIMBING: case PUSHING:
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
	case CUTTING:
	{
		int i = currentAnimation->GetCurrentFrame();

		if (currentAnimation == animationCut_LookingUp && animationCut_LookingUp->GetFirstFrame() == 0 && i == 10)
			animationCut_LookingUp->SetFrame(2, 9);
		//DebugOut(L"[LON] state: %d\n", currentAnimation->GetLastFrame());
		
		if (currentAnimation->isActionFinish())
		{
			/*GameSound::getInstance()->play(CUT_MUSIC);*/

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
			//case JUMPING:
			//{
			//	//animationCut_Jumping->SetFrame(0, 0);
			//	if ((vy != 0 && y + 20 < MAP_HEIGHT - 9))
			//	{
			//		Jump();
			//		DebugOut(L"[jump] state: %d\n", state);
			//	}
			//	else if (vy == 0 && y + 20 >= MAP_HEIGHT - 9)
			//	{
			//		//animationCut_Jumping->SetFrame(0, 5);
			//		Stand();
			//	}

			//	break;
			//}
			default:
			{				
				if (y + 20 < MAP_HEIGHT - 9)
					Jump();
				else
					Stand();
				break;
			}
			}			
		}
		if (lastState == JUMPING && vy == 0 && y + 20 >= MAP_HEIGHT - 9)
		{
			Stand();
		}

		// 10:43 13/11
		//switch (lastState)
		//{
		//case LOOK_UP:
		//{
		//	if (i == 11)
		//		Stand();

		//	break;
		//}
		//case DUCKING:
		//{
		//	if (i == 6)
		//	{
		//		if (KeyDown)
		//			Duck();
		//		else
		//			Stand();
		//	}

		//	break;
		//}
		//// 1:09 13/11
		//case JUMPING:
		//{
		//	if (vy == 0 && y + 20 >= MAP_HEIGHT - 9)
		//		Stand();

		//	break;
		//}
		//default:
		//{
		//	if (currentAnimation->isActionFinish())
		//		Stand();

		//	break;
		//}
		//}

		break;
	}
	default:
	{
		if (lastState == DUCKING && state != STANDING)
		{			
			state = lastState;
			Cut();
			break;
		}

		if (lastState == DUCKING && lastState == STANDING)
			lastState = STANDING;

		if (!(vy == 0 && y + 20 >= MAP_HEIGHT - 9))
		{
			state = JUMPING;
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

void CAladdin::Throw()
{
	switch (state)
	{
	case RUNNING: case RUN_LONG_ENOUGH: case SWINGING: case CLIMBING: case PUSHING:
		break;	
	case DUCKING:
	{
		lastState = DUCKING;
		SetState(THROWING);
		SetAnimation(ANI_THROW_DUCKING);
		vx = 0;
		keyUp[1] = false;
		isAppleCreated = false;

		break;
	}
	case JUMPING:
	{
		lastState = JUMPING;
		SetState(THROWING);
		SetAnimation(ANI_THROW_JUMPING);		
		keyUp[1] = false;
		isAppleCreated = false;

		break;
	}
	case THROWING:
	{
		int i = currentAnimation->GetCurrentFrame();		
		if ((currentAnimation == animationThrow_Standing && i == 3 || currentAnimation == animationThrow_Ducking && i == 3 || currentAnimation == animationThrow_Jumping && i == 3/* || i == 188*/) && isAppleCreated == false)
		{
			/*GameSound::getInstance()->play(THROW_MUSIC);*/

			CreateApple();
			isAppleCreated = true;
		}

		if (currentAnimation->isActionFinish())
		{
			/*GameSound::getInstance()->play(CUT_MUSIC);*/

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
			default:
			{				
				if (y + 20 < MAP_HEIGHT - 9)
					Jump();
				else
					Stand();
				break;
			}
			}
		}
		if (lastState == JUMPING && vy == 0 && y + 20 >= MAP_HEIGHT - 9)
		{
			Stand();
		}

		break;
	}
	default:
	{
		if (lastState == DUCKING && state != STANDING)
		{
			state = lastState;
			Throw();
			break;
		}

		if (lastState == DUCKING && lastState == STANDING)
			lastState = STANDING;

		if (!(vy == 0 && y + 20 >= MAP_HEIGHT - 9))
		{
			state = JUMPING;
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

void CAladdin::LookUp()
{
	switch (state)
	{
	case STANDING: case RUNNING: case RUN_LONG_ENOUGH:
	case WAITING_1: case WAITING_2:
	{
		lastState = STANDING;
		SetState(LOOK_UP);
		SetAnimation(ANI_LOOKUP_1);
		vx = 0;
		animationLookUp_1->SetFrame(0, 2);
		
		break;
	}
	case LOOK_UP: case CUTTING:
	{
		lastState = LOOK_UP;
		SetState(LOOK_UP);
		SetAnimation(ANI_LOOKUP_1);
		vx = 0;		

		int i = currentAnimation->GetCurrentFrame();

		if (i == 2)
			animationLookUp_1->SetFrame(2, 2);

		break;
	}
	}
}

void CAladdin::Jump()
{	
	switch (state)
	{	
	case RUNNING:
	{
		SetState(JUMPING);
		SetAnimation(ANI_JUMP_RUNNING);
		vy -= 0.4f;

		keyUp[2] = false;

		break;

	}
	case CUTTING: case THROWING:
	{
		////
		//if (lastState == SWING || lastState == CLIMB)
		//{
		//	state = lastState;
		//	Jump();
		//	break;
		//}//

		state = JUMPING;
		SetAnimation(ANI_JUMP_RUNNING);
		animationJump_Running->SetCurrentFrame(5);
		keyUp[2] = false;

		break;
	}
	case JUMPING:
	{
		//int i = animationJump_Standing->GetCurrentFrame();

		/*if (i == 9)
		animationJump_Standing->SetFrame(9, 9);*/

		if (vy == 0 && y + 20 >= MAP_HEIGHT - 9)
		{
			currentAnimation->ResetFrame();
			/*if (KeyRight || KeyLeft)
				Run();
			else
				Stand();*/
			Stand();
		}

		break;
	}
	default:
	{
		lastState = state;
		SetState(JUMPING);
		SetAnimation(ANI_JUMP_STANDING);
		vy -= 0.45f;						//start jump if is not "on-air"
		//animationJump_Standing->SetFrame(0, 9);

		keyUp[2] = false;

		break;
	}
	}
}

void CAladdin::Stand()
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
		/*if (state == JUMPING && last_vy >= 0.2f)
		{
			state = STANDING;
			vx = 0;
			SetAnimation(ANI_LAND_1);
			break;
		}*/

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

void CAladdin::Wait()
{
	DWORD startWait = GetTickCount();	
	int i = currentAnimation->GetCurrentFrame();
	switch (state)
	{
	case STANDING:
	{
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
	/*case WAITING_SWINGING:
	{
	if (currentAnimation->isActionFinish())
	{
	if (i == 4)
	animationWait_Swinging->SetFrame(0, 4);
	else
	animationWait_Swinging->SetFrame(4, 0);
	}
	break;
	}*/
	case SWING:
	{
		lastState = state;
		SetState(WAITING_SWINGING);
		SetAnimation(ANI_WAIT_SWINGING);
		//ANI_WAIT_SWINGING->SetFrame(183, 179);
		break;
	}

	}
}

void CAladdin::CreateApple()
{
	CGameObject* apple = new CApple();
	apple->id = 6;
	apple->SetObjectFromID();

	if (lastState == SWING || lastState == SWINGING || lastState == CLIMB || lastState == CLIMBING)
	{
		apple->yDraw = (this->Top() + this->Bottom()) / 2;
		// vận tốc ném lên (vy) của táo, ném ngang thì vx
		apple ->vy = -0.07f;
		if (!direction)
		{
			apple->xDraw = this->Right();
			apple->vx = 0.4f;
		}
		else
		{
			apple->xDraw = this->Left();
			apple->vx = -0.4f;
		}
	}
	else
	{
		apple->yDraw = this->Top();
		// vận tốc ném lên (vy) của táo, ném ngang thì vx
		apple->vy = -0.1f;
		if (direction)
		{
			apple->xDraw = this->Right();
			apple->vx = 0.35f;
		}
		else
		{
			apple->xDraw = this->Left();
			apple->vx = -0.35f;
		}
	}

	apple->direction = this->direction;
	apple->LoadResources();
	listApples.push_back(apple);
}

vector<CGameObject*>* CAladdin::GetListApples()
{
	return &listApples;
}

void CAladdin::DeleteApple(CGameObject * apple)
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

void CAladdin::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;
	currentAnimation->SetCurrentSize(w, h);

	if (vy > 0)
		last_vy = vy;
	//simulate fall down (gravity)
	vy += 0.02f;

	if (x < 30 || x + 20 > MAP_WIDTH - 30)
		vx = 0, vy = 0;
	else if (y < 30 || y + 20 >= MAP_HEIGHT - 9)
	{
		vy = 0;
		y = MAP_HEIGHT - 9 - 20;
	}		

	for (int i = 0; i < listApples.size(); i++)
	{
		listApples[i]->Update(dt);
	}
}

void CAladdin::Render()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - CCamera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - CCamera::GetInstance()->GetPosition().y));
	currentAnimation->Render(x, y, xDraw, yDraw, direction, trans);

	for (int i = 0; i < listApples.size(); i++)
	{
		listApples[i]->Render();
	}
}

void CAladdin::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = xDraw;
	t = yDraw;
	r = xDraw + w;
	b = yDraw + h;
}

void CAladdin::SetAnimation(int ani)
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
	case ANI_JUMP_SWINGING:
	{
		currentAnimation = animationJump_Swinging;
		currentAnimation->ResetFrame();
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
	case ANI_CUT_SWINGING:
	{
		currentAnimation = animationCut_Swinging;
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
	case ANI_THROW_SWINGING:
	{
		currentAnimation = animationThrow_Swinging;
		currentAnimation->ResetFrame();
		break;
	}
	case ANI_BRAKE_1:
	{
		currentAnimation = animationBrake_1;
		currentAnimation->ResetFrame();
		break;
	}
	}
}

void CAladdin::SetPosition(float x, float y)
{
	float distance_x = this->x - xDraw;
	float distance_y = this->y - yDraw;

	this->x = x;
	this->y = y;
	xDraw = x - distance_x;
	yDraw = y - distance_y;
}

//void CAladdin::SetRanDomPosition()
//{
//	float xRand = 30 + rand() % RANDOM_WIDTH - 29;
//	float yRand = 30 + rand() % RANDOM_HEIGHT - 29;
//	SetPosition(xRand, yRand);
//}

void CAladdin::CheckCollision(vector<LPGAMEOBJECT> *coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	DebugOut(L"[KT] coObjs: %d\n", coObjects->size());

	CalcPotentialCollisions(coObjects, coEvents);

	//DebugOut(L"[BEFO] collision: %d\n", coEvents.size());

	// No collision occured, proceed normally		
	if (coEvents.size() == 0)
	{
		// debug
		//DebugOut(L"[NONE] collision: %d\n", coEvents.size());	

		if (this->xDraw < 0)
		{
			vx = 0;
			this->x = 0;
		}
		else if (this->yDraw < 0)
		{
			vy = 0;
			this->y = 0;
		}
		else if (this->xDraw > MAP_WIDTH - BALL_BBOX_WIDTH)
		{
			vx = 0;
			this->xDraw = MAP_WIDTH - BALL_BBOX_WIDTH;
		}
		else if (this->yDraw > MAP_HEIGHT - BALL_BBOX_HEIGHT)
		{
			vy = 0;
			this->y = MAP_HEIGHT - BALL_BBOX_HEIGHT;
		}
		else
		{
			x += dx;
			y += dy;
		}
	}
	// Collision occured with the bars
	else
	{
		// debug
		//DebugOut(L"[COLL] collision: %d\n", coEvents.size());

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// Collision logic with s.t
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CAladdin *>(e->obj)) // if e->obj is s.t 
			{
				CAladdin *otherBall = dynamic_cast<CAladdin *>(e->obj);

				//if (e->nx < 0)			// touch leftside of otherBall
				//{
				//	vx = -(vx + 0.1);	
				//}
				//else if (e->nx > 0)		// touch rightside of otherBall
				//{
				//	vx = -(vx - 0.1);
				//}
				//else if (e->ny < 0)		// touch topside of otherBall
				//{
				//	vy = -(vy + 0.1);
				//}
				//else if (e->ny > 0)		// touch botside of otherBall
				//{
				//	vy = -(vy - 0.1);
				//}

				if (e->nx != 0)				// touch left,rightside of otherBall
					vx = -vx;
				else if (e->ny != 0)		// touch top,botside of otherBall
				{
					vy = -vy;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

CAladdin * CAladdin::GetInstance()
{	
	if (__instance == NULL) __instance = new CAladdin();
	return __instance;
}

//void CAladdin::SetSpeed()
//{
//	int randomx = rand() % 2;
//	int randomy = rand() % 2;
//
//	vx = speed[randomx];
//	vy = speed[randomy];
//}
