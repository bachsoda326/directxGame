#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Constants.h"
#include "Sprites.h"

using namespace std;

/*#define ID_TEX_BBOX -100	*/	// special texture to draw object bounding box

enum CollisionType
{
	CollGround,
	CollRope,
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

enum ObjectType
{
	OBJGround,
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

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
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
	float dx, dy;	// dx = vx*dt; dy = vy*dt

	CollisionType collType;
	ObjectType objType;
	/*int nx;*/
	int nx, ny;

	// trạng thái
	int state;
	// chuyển động
	int animation;
	// hướng của đối tượng; phải = true, trái = false
	bool direction;

	DWORD dt;

	vector<LPANIMATION> animations;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	D3DXVECTOR3 GetPosition() { return D3DXVECTOR3(x, y, 0); }

	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }	
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }

	void AddAnimation(int aniId);

	void RenderBoundingBox();

	float Left();
	float Top();
	float Right();	
	float Bottom();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);	

	CGameObject();

	//set type object from object's id
	virtual void SetObjectFromID();
	virtual void LoadResources();
	virtual void SetState(int state) { this->state = state; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;

	~CGameObject();
};

