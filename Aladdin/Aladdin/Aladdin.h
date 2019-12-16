#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Camera.h"
#include "Game.h"
#include "Collision.h"

class Aladdin : public GameObject
{
public:
	int blood;			// máu
	int score;			// điểm
	int numRubies;		// số ruby
	int numLifes;		// số mạng
	int numApples;		// số apple
	bool isCutted;

private:
	static Aladdin * __instance;

	Game *keyBoard = Game::GetInstance();
	// các biến để chỉ cho nhảy, chém, ném 1 lần
	bool keyUp[3];
	// ứng với mũi tên lên, xuống, Z, X, cách, trái, phải
	bool KeyUp, KeyDown, KeyZ, KeyX, KeySpace, KeyLeft, KeyRight;

	// t.gian đứng
	DWORD standingTime;
	// trạng thái cuối
	int lastState;
	// v.tốc vy cuối
	float lastVy;

	bool isAppleCreated;
	// biến đếm animation Wait_1
	int isBlink;
	//Lưu thời gian lúc bắt đầu nhấp nháy
	DWORD startBlink;

	int countWait_1;
	// :test số lần nhận đc collision
	int testCollision = 0;

public:
	Aladdin();	
	static Aladdin * GetInstance();

	// các animation
	LPANIMATION animationWait_1,
		animationWait_2,
		animationWait_3,
		animationWait_Swinging,
		animationStand_1,
		animationLookUp_1,
		animationRun_1,
		animationLand_1,
		animationDuck_1,
		animationJump_Standing,
		animationJump_Running,
		animationJump_Climbing,
		animationClimb_1,
		animationCut_Standing,
		animationCut_LookingUp,
		animationCut_Ducking,
		animationCut_Jumping,
		animationCut_Climbing,
		animationThrow_Standing,
		animationThrow_Ducking,
		animationThrow_Jumping,
		animationThrow_Climbing,
		animationBrake_1,
		animationPush,
		animationHurt,
		animationDie,
		animationRespawn;

	// các trạng thái
	enum AladdinStates
	{
		STANDING,
		RUNNING,
		CUTTING,
		DUCKING,			// cúi xuống
		WAITING_1,
		WAITING_2,
		WAITING_3,
		WAITING_SWINGING,			
		RUN_LONG_ENOUGH,	// chạy đủ lâu
		BRAKING,			// thắng lại (khi chạy đủ lâu)
		JUMPING,
		THROWING,			// ném
		LOOK_UP,			// nhìn lên
		CLIMB,				// leo trèo
		CLIMBING,
		FALL,				// rớt
		FALLCLIMB,			// rớt khi đu dây xích
		SWINGING,
		PUSHING,			// đẩy (khi gặp tường mà k đi đc)
		STUNTING,
		HURT,
		DIE,
		RESETPOSITION,
		RUNNEXT,
		FLY,
		HUG
	};

	// các trạng thái đại diện animation
	enum AladdinAnimations
	{
		ANI_WAIT_1,
		ANI_WAIT_2,
		ANI_WAIT_3,
		ANI_WAIT_SWINGING,
		ANI_STAND_1,
		ANI_LOOKUP_1,
		ANI_RUN_1,
		ANI_LAND_1,
		ANI_DUCK_1,
		ANI_JUMP_STANDING,
		ANI_JUMP_RUNNING,
		ANI_JUMP_CLIMBING,
		ANI_CUT_STANDING,
		ANI_CUT_LOOKINGUP,
		ANI_CUT_DUCKING,
		ANI_CUT_JUMPING,
		ANI_CUT_CLIMBING,
		ANI_THROW_STANDING,
		ANI_THROW_DUCKING,
		ANI_THROW_JUMPING,
		ANI_THROW_CLIMBING,
		ANI_BRAKE_1,		
		ANI_RUN_LONG_ENOUGH,
		ANI_PUSH,
		ANI_HURT,
		ANI_DIE,
		ANI_RESPAWN,
		ANI_000000000000000,
		ANI_CLIMB_1,
		ANI_CLIMBING,
		ANI_SWING,
		ANI_SWINGING,		
		ANI_STUNTING,		
		ANI_RUNNEXT,
		ANI_FLY,
		ANI_HUG
	};

	// Khởi tạo obj
	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);	
	void Render();

	void SetAnimation(AladdinAnimations ani);

	// Update nhận các phím đc nhấn
	void UpdateKey();
	// Xử lý các sự kiện nhấn phím
	void HandleKeyBoard();

	void Stand();	// đứng yên
	void Wait();	// đợi (khi đứng yên 1 t.gian)	
	void Duck();	// cúi xuống
	void LookUp();	// nhìn lên
	void Run();		// chạy
	void Brake();	// thắng lại
	void Push();	// đẩy khi bị chặn
	void Jump();	// nhảy
	void Climb();	// leo
	void Cut();		// chém
	void Throw();	// ném (táo)	
	void Hurt();
	void Die();
	void ResetPosition();

	// Handle apple
	vector<GameObject*> listApples;
	vector<GameObject*>* GetListApples();
	void CreateApple();
	//void CreateApple(GameObject*obj);	
	void DeleteApple(GameObject* apple);

	void OnCollision(GameObject *obj, float nx, float ny);
	void OnIntersect(GameObject *obj);
	/*Camera *camera;
	void SetCamera(Camera *camera);*/
};

