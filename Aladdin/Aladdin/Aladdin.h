#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Camera.h"
#include "Game.h"
#include "Collision.h"

class Aladdin : public GameObject
{
private:
	static Aladdin * __instance;

	Game *keyBoard = Game::GetInstance();
	// các biến để chỉ cho nhảy, chém, ném 1 lần
	bool keyUp[3];
	// ứng với mũi tên lên, xuống, Z, X, cách, trái, phải
	bool KeyUp, KeyDown, KeyZ, KeyX, KeyC, KeyLeft, KeyRight;
	
	// trạng thái cuối
	int lastState;
	// true: đã tạo táo | false: chưa tạo táo
	bool isAppleCreated;
	// 0: k mờ | 1: bị mờ (k thể bị thương)
	int isBlink;
	// t.gian đứng
	DWORD standingTime;
	// t.gian lúc b.đầu mờ
	DWORD startBlink;
	// biến đếm khi đủ lớn sẽ chuyển animation từ Wait_1 sang Wait_2
	int countWait_1;
	// list táo
	vector<GameObject*> listApples;
	
public:
	// các trạng thái
	enum AladdinStates
	{
		STANDING,					// đứng
		RUNNING,					// chạy
		CUTTING,					// chém
		DUCKING,					// cúi xuống
		WAITING_1,					// đợi 1
		WAITING_2,					// đợi 2
		WAITING_3,					// đợi 3
		RUN_LONG_ENOUGH,			// chạy đủ lâu
		BRAKING,					// thắng lại (khi chạy đủ lâu)
		JUMPING,					// nhảy
		THROWING,					// ném
		LOOK_UP,					// nhìn lên
		CLIMB,						// leo trèo
		CLIMBING,					// đang trèo
		FALL,						// rớt
		FALLCLIMB,					// rớt khi đu dây xích
		PUSHING,					// đẩy (khi gặp tường mà k đi đc)
		HURT,						// bị thương
		DIE,						// chết
		RESETPOSITION,				// hồi sinh
		RUNNEXT,					// chạy qua màn
		FLY,						// bay
		HUG							// ôm nhau
	};
	// các trạng thái đại diện animation
	enum AladdinAnimations
	{
		ANI_WAIT_1,					// đợi 1
		ANI_WAIT_2,					// đợi 2
		ANI_WAIT_3,
		ANI_WAIT_SWINGING,
		ANI_STAND_1,				// đứng
		ANI_LOOKUP_1,				// nhìn lên
		ANI_RUN_1,					// chạy
		ANI_LAND_1,	
		ANI_DUCK_1,					// cúi xuống
		ANI_JUMP_STANDING,			// nhảy khi đứng
		ANI_JUMP_RUNNING,			// nhảy khi chạy
		ANI_JUMP_CLIMBING,			// nhảy khi trèo
		ANI_CUT_STANDING,			// chém khi đứng
		ANI_CUT_LOOKINGUP,			// chém khi nhìn lên
		ANI_CUT_DUCKING,			// chém khi cúi xuống
		ANI_CUT_JUMPING,			// chém khi nhảy
		ANI_CUT_CLIMBING,			// chém khi tròe
		ANI_THROW_STANDING,			// ném khi đứng
		ANI_THROW_DUCKING,			// ném khi cúi xuống
		ANI_THROW_JUMPING,			// ném khi nhảy
		ANI_THROW_CLIMBING,			// ném khi trèo
		ANI_BRAKE_1,				// thắng lại
		ANI_PUSH,					// đẩy
		ANI_HURT,					// bị thương
		ANI_DIE,					// chết
		ANI_RESPAWN,				// hồi sinh
		ANI_RUNNEXT,				// chạy qua màn
		ANI_FLY,					// bay
		ANI_HUG,					// ôm
		ANI_CLIMB_1,				// trèo
		ANI_CLIMBING,				// đang trèo
	};
	LPANIMATION animationWait_1,	// đợi 1
		animationWait_2,			// đợi 2
		animationWait_3,			// đợi 3
		animationWait_Swinging,		
		animationStand_1,			// đứng
		animationLookUp_1,			// nhìn lên
		animationRun_1,				// chạy
		animationLand_1,			
		animationDuck_1,			// cúi xuống
		animationJump_Standing,		// nhảy khi đứng
		animationJump_Running,		// nhảy khi chạy
		animationJump_Climbing,		// nhảy khi trèo
		animationClimb_1,			// trèo
		animationCut_Standing,		// chém khi đứng
		animationCut_LookingUp,		// chém khi nhìn lên
		animationCut_Ducking,		// chém khi cúi xuống
		animationCut_Jumping,		// chém khi nhảy
		animationCut_Climbing,		// chém khi trèo
		animationThrow_Standing,	// ném khi đứng
		animationThrow_Ducking,		// ném khi cúi xuống
		animationThrow_Jumping,		// ném khi nhảy
		animationThrow_Climbing,	// ném khi trèo
		animationBrake_1,			// thắng lại
		animationPush,				// đẩy
		animationHurt,				// bị thương
		animationDie,				// chết
		animationRespawn,			// hồi sinh
		animationRunNext,			// chạy qua màn
		animationEndFly,			// bay
		animationEndHug;			// ôm nhau

	int blood;						// máu
	int score;						// điểm
	int numRubies;					// số ruby
	int numLifes;					// số mạng
	int numApples;					// số táo	

public:
	Aladdin();	
	static Aladdin * GetInstance();

	void LoadResources();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);	
	void Render();

	// Action của Aladdin
	void Stand();					// đứng
	void Wait();					// đợi (khi đứng yên 1 t.gian)	
	void Duck();					// cúi xuống
	void LookUp();					// nhìn lên
	void Run();						// chạy
	void Brake();					// thắng lại
	void Push();					// đẩy khi bị chặn
	void Jump();					// nhảy
	void Climb();					// leo
	void Cut();						// chém
	void Throw();					// ném (táo)	
	void Hurt();					// bị thương
	void Die();						// chết
	void RunNextScene();			// chạy qua màn
	void Fly();						// bay
	void Hug();						// ôm nhau
	void ResetPosition();			// hồi sinh

	void SetAnimation(AladdinAnimations ani);

	// Update nhận các phím đc nhấn
	void UpdateKey();
	// Xử lý các sự kiện nhấn phím
	void HandleKeyBoard();	
	
	// Lấy list táo
	vector<GameObject*>* GetList();
	// Tạo táo
	void CreateApple();
	void DeleteApple(GameObject* apple);

	// Va chạm vs đất, hàng rào, gạch đá
	void OnCollision(GameObject *obj, float nx, float ny);
	// Giao nhau vs các obj còn lại
	void OnIntersect(GameObject *obj);	
};

