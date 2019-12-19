#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Constants.h"
#include "Sprites.h"
#include "debug.h"
#include "Textures.h"
#include "Camera.h"
#include "GameSound.h"

using namespace std;

// kiểu va chạm
enum CollisionType
{
	CollGround,					// kiểu va chạm mặt đất
	CollFence,					// kiểu va chạm hàng rào
	CollBrick,					// kiểu va chạm gạch đá
	CollChains,					// kiểu va chạm dây xích
	CollApple,					// kiểu va chạm táo
	CollAladdin,				// kiểu va chạm Aladdin
	CollEnemy,					// kiểu va chạm địch
	CollItem,					// kiểu va chạm item
	CollFireCarpet,				// kiểu va chạm thảm lửa
	CollStar,					// kiểu va chạm sao (do Boss bắn ra)
	CollUnknown					// kiểu va chạm khác
};

// kiểu obj
enum ObjectType
{
	OBJGround,					// OBJ mặt đất
	OBJFence,					// OBJ hàng rào
	OBJApple,					// OBJ táo
	OBJItem,					// OBJ item
	OBJBlueHeart,				// OBJ tim xanh
	OBJGenieFace,				// OBJ mặt Genie
	OBJGenieJar,				// OBJ bình Genie (điểm hồi sinh)
	OBJRuby,					// OBJ ruby
	OBJNormalGuard,				// OBJ enemy béo
	OBJThinGuard,				// OBJ enemy gầy
	OBJAladdin,					// OBJ Aladdin
	OBJAbu,						// OBJ khỉ Abu
	OBJBoss,					// OBJ Boss
	OBJStar,					// OBJ sao (do Boss bắn ra)	
	OBJBat,						// OBJ dơi
	OBJBoomSkeleton,			// OBJ bộ xương boom
	OBJBone,					// OBJ xương (do bộ xương boom tạo)
	OBJPeddler,					// OBJ người bán hàng
	OBJStall,					// OBJ shop (của người bán hàng)
	OBJBallTrap,				// OBJ bẫy bóng
	OBJSharpTrap,				// OBJ bẫy nhọn
	OBJStoneBrick,				// OBJ gạch đá
	OBJFireCarpet,				// OBJ thảm lửa
	OBJFire						// OBJ lửa
};

class GameObject;
typedef GameObject * LPGAMEOBJECT;

class GameObject
{
public:
	int id;
	// id của cell grid chứa obj
	int cellIndex;

	// c.bị chết 
	bool isDie;
	// đã chết
	bool isDead;
	// true: đã đc ăn | false: chưa đc ăn
	bool isActived;

	// vị trí ban đầu của các đối tượng
	float xInit, yInit;
	// vị trí
	float x, y;
	// dài rộng
	float w, h;
	// vị trí vẽ (để cân xứng giữa các frame hình của animation)
	float xDraw, yDraw;
	// vận tốc	
	float vx, vy;
	// dx = vx*dt; dy = vy*dt
	float dx, dy;
	// kiểu va chạm
	CollisionType collType;
	// kiểu obj
	ObjectType objType;
	// hướng có khả năng va chạm nx ngang ny dọc
	float nx, ny;

	// trạng thái
	int state;
	// animation hiện tại
	LPANIMATION currentAnimation;
	// hướng của đối tượng; phải = true, trái = false
	bool direction;

	DWORD dt;

public:
	GameObject();

	// Set vị trí
	void SetPosition(float x, float y);
	// Set vận tốc
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	D3DXVECTOR3 GetPosition() { return D3DXVECTOR3(x, y, 0); }	
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int GetState() { return this->state; }	

	// Trả về các biên(của RECT) của obj
	float Left();
	float Top();
	float Right();	
	float Bottom();
		
	// Khởi tạo obj
	virtual void LoadResources();
	// Update trạng thái hoạt động obj
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	// Vẽ obj
	virtual void Render();
	// Vẽ RECT của obj
	void RenderBoundingBox();

	// Set trạng thái cho obj
	virtual void SetState(int state) { this->state = state; }		
	// Get biên(RECT) obj 
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	// Get list obj con đc tạo of OBJ đang xét 
	virtual vector<GameObject*>* GetList();
	// Khôi phục các thuộc tính
	virtual void ResetProper();

	// Đổi và reset frame size (khoảng cách để xét va chạm với các obj khác)
	virtual void ChangeFrameSize(GameObject*obj);
	virtual void ResetFrameSize(GameObject*obj);

	// Va chạm (Aladdin với ground (đất, gỗ, hàng rào, cột))
	virtual void OnCollision(GameObject*obj, float nx, float ny);
	// Giao nhau (Aladdin vs item, enemy, dây xích đu; ném táo vs ground, enemy)
	virtual void OnIntersect(GameObject*obj);

	~GameObject();
};

