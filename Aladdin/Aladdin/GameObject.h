#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Constants.h"
#include "Sprites.h"
#include "debug.h"
#include "Textures.h"
#include "Camera.h"

using namespace std;

// kiểu va chạm
enum CollisionType
{
	CollGround,
	CollFence,
	CollBrick,
	CollChains,
	CollCollarBeam,
	CollStair,
	CollCamel,
	CollApple,
	CollLine,
	CollAladdin,
	CollEnemy,
	CollItem,
	CollRod,
	CollFireCarpet,
	CollStar,
	CollUnknown
};

// kiểu obj
enum ObjectType
{
	OBJGround,
	OBJFence,
	OBJRope,
	OBJCollarBeam,
	OBJStair,
	OBJCamel,
	OBJApple,
	OBJJarThrower,
	OBJSwordsman,
	OBJRod,
	OBJItem,
	OBJSpittle,
	OBJSword,
	OBJJar,
	OBJAbuItem,
	OBJBlueHeart,
	OBJGenieFace,
	OBJGenieJar,
	OBJLamp,
	OBJRuby,
	OBJGuard1,
	OBJGuard2,
	OBJGuard3,
	OBJTheft,
	OBJFireCarpet,
	OBJFire,
	OBJLine,
	OBJFallingGround,
	OBJAladdin,
	OBJBoss,
	OBJStar,
	OBJAladdinFace,
	OBJAbu,
	OBJKnives,
	OBJBird,
	OBJGenie
};

class GameObject;
typedef GameObject * LPGAMEOBJECT;

// Sự kiện va chạm
struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;
struct CollisionEvent
{
	LPGAMEOBJECT obj;
	// t.gian, hướng va chạm ngang, hướng va chạm dọc
	float t, nx, ny;
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class GameObject
{
public:
	int id, _id;
	// active dùng cho các đối tượng có kiểu va chạm là Item
	bool isDie, isDead, isActived;

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

	CollisionType collType;
	ObjectType objType;
	// hướng có khả năng va chạm x ngang y dọc
	float nx, ny;

	// trạng thái
	int state;
	LPANIMATION currentAnimation;
	// hướng của đối tượng; phải = true, trái = false
	bool direction;

	DWORD dt;

public:
	GameObject();

	void SetPosition(float x, float y);
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	D3DXVECTOR3 GetPosition() { return D3DXVECTOR3(x, y, 0); }	
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int GetState() { return this->state; }	

	// Vẽ RECT của obj
	void RenderBoundingBox();

	// Trả về các biên(của RECT) của obj
	float Left();
	float Top();
	float Right();	
	float Bottom();

	// Mở rộng vủa SweptAABB để xử lý va chạm 2 obj di chuyển
	//LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	// Trường hợp đặc biệt khi va chạm(chủ yếu là khi va chạm ngang dọc vs đất, cột)
	//void ExceptionCase(LPGAMEOBJECT coObj, float &t, float &nx, float &ny);
	/*
	Tính toán các obj có thể va chạm vs obj đang gọi hàm
	coObjects: listObjs có thể va chạm
	coEvents: list va chạm có thể xảy ra
	*/
	//void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	/*void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);*/

	// Khởi tạo obj
	virtual void LoadResources();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	//process input
	virtual void ProcessInput();
	// Set kiểu object từ object's id
	virtual void SetObjectFromID();
	// Set trạng thái cho obj
	virtual void SetState(int state) { this->state = state; }
		
	// Get biên(RECT) obj 
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	//change and reset frame size
	virtual void ChangeFrameSize(GameObject*obj);
	virtual void ResetFrameSize(GameObject*obj);

	virtual void OnCollision(GameObject*obj, float nx, float ny);
	virtual void OnIntersect(GameObject*obj);

	~GameObject();
};

