#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Camera.h"
#include "Game.h"

//#define BALL_BBOX_WIDTH  16
//#define BALL_BBOX_HEIGHT 16
//#define BALL_SPEED 0.1f

class CAladdin : public CGameObject
{
private:
	static CAladdin * __instance;
	CGame *keyBoard = CGame::GetInstance();
	DWORD standingTime;
	int lastState;
	float last_vy;

	bool keyUp[3];
	bool KeyUp, KeyDown, KeyZ, KeyX, KeySpace, KeyLeft, KeyRight;
	bool isAppleCreated;

	float speed[2] = { -BALL_SPEED, BALL_SPEED };
public:
	CAladdin();	

	LPANIMATION currentAnimation,
		animationWait_1,
		animationWait_2,
		animationWait_Swinging,
		animationStand_1,
		animationLookUp_1,
		animationRun_1,
		animationLand_1,
		animationDuck_1,
		animationJump_Standing,
		animationJump_Running,
		animationJump_Swinging,
		animationCut_Standing,
		animationCut_LookingUp,
		animationCut_Ducking,
		animationCut_Jumping,
		animationCut_Swinging,
		animationThrow_Standing,
		animationThrow_Ducking,
		animationThrow_Jumping,
		animationThrow_Swinging,
		animationBrake_1;

	enum AladdinStates
	{
		STANDING,
		RUNNING,
		CUTTING,
		DUCKING,
		WAITING_1,
		WAITING_2,
		WAITING_SWINGING,			
		RUN_LONG_ENOUGH,
		BRAKING,		
		JUMPING,
		THROWING,
		LOOK_UP,		
		CLIMB,
		CLIMBING,
		SWING,
		SWINGING,
		PUSHING,
		STUNTING,
		HURT,
		DIE,
		RESETPOSITION,
		RUNNEXT,
		FLY,
		HUG
	};

	enum AladdinAnimations
	{
		ANI_WAIT_1,
		ANI_WAIT_2,
		ANI_WAIT_SWINGING,
		ANI_STAND_1,
		ANI_LOOKUP_1,
		ANI_RUN_1,
		ANI_LAND_1,
		ANI_DUCK_1,
		ANI_JUMP_STANDING,
		ANI_JUMP_RUNNING,
		ANI_JUMP_SWINGING,
		ANI_CUT_STANDING,
		ANI_CUT_LOOKINGUP,
		ANI_CUT_DUCKING,
		ANI_CUT_JUMPING,
		ANI_CUT_SWINGING,
		ANI_THROW_STANDING,
		ANI_THROW_DUCKING,
		ANI_THROW_JUMPING,
		ANI_THROW_SWINGING,
		ANI_BRAKE_1,
		ANI_000000000000000,
		ANI_RUN_LONG_ENOUGH,
		ANI_CLIMB,
		ANI_CLIMBING,
		ANI_SWING,
		ANI_SWINGING,
		ANI_PUSHING,
		ANI_STUNTING,
		ANI_HURT,
		ANI_DIE,
		ANI_RESETPOSITION,
		ANI_RUNNEXT,
		ANI_FLY,
		ANI_HUG
	};

	void LoadResources();

	/*CCamera *camera;
	void SetCamera(CCamera *camera);*/

	//update key
	void UpdateKey();
	void HandleKeyBoard();

	void Run();
	void Brake();
	void Duck();
	void Cut();
	void Throw();
	void LookUp();
	void Jump();
	void Stand();
	void Wait();

	//handle apple
	vector<CGameObject*> listApples;
	void CreateApple();
	//void CreateApple(CGameObject*obj);
	vector<CGameObject*>* GetListApples();
	void DeleteApple(CGameObject* apple);
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetAnimation(int ani);
	void SetPosition(float x, float y);
	void SetRanDomPosition();
	void CheckCollision(vector<LPGAMEOBJECT> *coObjects);
	//void SetSpeed();

	static CAladdin * GetInstance();
};

