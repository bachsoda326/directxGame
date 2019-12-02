#include "Collision.h"

Collision::Collision()
{
}

//check collision between 2 GameObject*(retangle)
float Collision::SweptAABB(GameObject* obj1, GameObject* obj2, float& nx, float& ny)
{
	float t = -1.0f;			// no collision
	nx = ny = 0;

	if (obj1->dx == 0 && obj1->dy == 0) 
		return t;

	//distance is the nearest between two GameObject*
	float dx_entry, dy_entry;
	//distance is the farest between two GameObject*
	float dx_exit, dy_exit;
	
	//find the distance between two GameObject on near and far GameObject's side
	//obj1 chạy theo hướng từ trái sang phải
	if (obj1->dx > 0.0f)
	{
		dx_entry = obj2->Left() - obj1->Right();
		dx_exit = obj2->Right() - obj1->Left();
	}
	//obj1 chạy theo hướng từ phải sang trái (dx_entry, tx_exit <= 0)
	else
	{
		dx_entry = obj2->Right() - obj1->Left();
		dx_exit = obj2->Left() - obj1->Right();
	}

	//obj1 chạy theo hướng từ trên xuống dưới
	if (obj1->dy > 0.0f)
	{
		dy_entry = obj2->Top() - obj1->Bottom();
		dy_exit = obj2->Bottom() - obj1->Top();
	}
	//obj1 chạy theo hướng từ dưới lên trên (dy_entry, ty_exit <= 0)
	else
	{
		dy_entry = obj2->Bottom() - obj1->Top();
		dy_exit = obj2->Top() - obj1->Bottom();
	}

	//find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float tx_entry, ty_entry;
	float tx_exit, ty_exit;

	if (obj1->dx == 0.0f)
	{
		tx_entry = -std::numeric_limits<float>::infinity();
		tx_exit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tx_entry = dx_entry / (obj1->dx);
		tx_exit = dx_exit / (obj1->dx);
	}

	if (obj1->dy == 0.0f)
	{
		ty_entry = -std::numeric_limits<float>::infinity();
		ty_exit = std::numeric_limits<float>::infinity();
	}
	else
	{
		ty_entry = dy_entry / (obj1->dy);
		ty_exit = dy_exit / (obj1->dy);
	}

	if (tx_entry < 0.0f && ty_entry < 0.0f || tx_entry > 1.0f || ty_entry > 1.0f)
		return t;

	//find the earliest/lastest times of collision
	float t_entry = max(tx_entry, ty_entry);
	float t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return t;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx_entry < 0 ? nx = 1.0f : nx = -1.0f;
	}
	else
	{
		nx = 0.0f;
		dy_entry < 0 ? ny = 1.0f : ny = -1.0f;
	}
}

//check broad-phasing
GameObject* Collision::GetSweptBroadphaseBaseObject(GameObject* obj)
{
	GameObject* broadPhase = new GameObject();

	broadPhase->xDraw = obj->dx > 0 ? obj->xDraw : obj->xDraw + obj->dx;
	broadPhase->yDraw = obj->dy > 0 ? obj->yDraw : obj->yDraw + obj->dy;
	broadPhase->w = obj->dx > 0 ? obj->w + obj->dx : obj->w - obj->dx;
	broadPhase->h = obj->dy > 0 ? obj->h + obj->dy : obj->h - obj->dy;

	return broadPhase;
}

bool Collision::AABBCheck(GameObject* obj1, GameObject* obj2)
{
	// return true nếu collision xảy ra
	return !(obj1->Right()<obj2->Left() || obj1->Left()>obj2->Right() || obj1->Bottom()<obj2->Top() || obj1->Top()>obj2->Bottom());
}

//check 2 GameObject* collised
void Collision::CheckCollision(GameObject* obj1, GameObject* obj2)
{
	//kiểm tra đã đặt lại kích thước box chưa
	bool isResetFrameSize = false;

	if (obj1->isDie || obj2->isDie || obj1 == obj2)
		return;

	obj1->ChangeFrameSize(obj2);
	obj2->ChangeFrameSize(obj1);

	if (AABBCheck(obj1, obj2))
	{
		obj1->ResetFrameSize(obj2);
		obj2->ResetFrameSize(obj1);
		isResetFrameSize = true;
		obj1->OnIntersect(obj2);
		obj2->OnIntersect(obj1);
	}

	if (!isResetFrameSize)
	{
		obj1->ResetFrameSize(obj2);
		obj2->ResetFrameSize(obj1);
	}

	if (obj1->x > obj2->Left() && obj1->x < obj2->Right() && obj2->objType == OBJGround)
	{
		if (obj2->Top() - obj1->y <= obj1->h * 1 / 2 && obj2->Top() - obj1->y > 0)
			obj1->ny = -1.0;
	}

	//broadPhase là đối tượng trong tương lai của obj1 (vị trí obj1 ở frame sau)
	GameObject* broadPhase = GetSweptBroadphaseBaseObject(obj1);
	if (AABBCheck(broadPhase, obj2))
	{
		float nx, ny;
		float collisionTime = SweptAABB(obj1, obj2, nx, ny);
		ExceptionalCase(obj1, obj2, nx, ny, collisionTime);

		//Cập nhật lại nx, ny
		if (nx != 0)
			obj1->nx = nx;
		if (ny != 0)
			obj1->ny = ny;

		//FilterCollision(collisionTime, obj1->nx, obj1->ny, nx, ny);
		
		// Xử lý va chạm obj1 với obj2, obj2 với obj1
		if (collisionTime <= 1.0f && collisionTime >= 0)
		{
			obj1->OnCollision(obj2, nx, ny);
			obj2->OnCollision(obj1, nx, ny);
		}
	}

	delete broadPhase;
}

//trường hợp ngoại lệ của va chạm, trả về collisionTime
void Collision::ExceptionalCase(GameObject* obj1, GameObject* obj2, float& nx, float& ny, float& collisionTime)
{

	if (obj2->collType == CollCollarBeam || obj2->collType == CollItem)
	{
		ny = 0;
		nx = 0;
		collisionTime = 1.0f;
		return;
	}

	if (obj1->x > obj2->Left() && obj1->x < obj2->Right())
	{
		if ((int)obj1->y >= (int)obj2->Top() && (int)obj1->y <= (int)obj2->Top() + 35 && obj1->vy > 0)
		{
			ny = -1.0f;
			nx = 0;
			collisionTime = 0.0f;
			return;
		}		
	}

	if (obj1->Top()<obj2->Bottom() - 20 && obj1->Bottom()>obj2->Top() + 20 && obj2->collType == CollFence)
	{
		if (obj1->Right() >= obj2->Left() && obj1->Right() < obj2->Right() && obj1->vx > 0 && obj1->direction)
		{
			nx = -1.0f;
			ny = 0;
			collisionTime = 0.0f;
			return;
		}

		if (obj1->Left() <= obj2->Right() && obj1->Left() > obj2->Left() && obj1->vx < 0 && !obj1->direction)
		{
			nx = 1.0f;
			ny = 0;
			collisionTime = 0.0f;
			return;
		}
	}
}

void Collision::FilterCollision(float & t, float & nx, float & ny, float dnx, float dny)
{
	float min_tx = 1.0f;
	float min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;
		
	if (t < min_tx && dnx != 0) {
		min_tx = t; nx = dnx; min_ix = 0;
	}

	if (t < min_ty  && dny != 0) {
		min_ty = t; ny = dny; min_ix = 0;
	}

	if (min_ix != 0)
		t = -1.0f;
}

//obj obj1 là đối tượng di chuyển, obj obj2 là đối tượng tĩnh
void Collision::PreventMove(GameObject* obj1, GameObject* obj2, float nx, float ny)
{
	/*if (obj1->x > obj2->Left() && obj1->x < obj2->Right())
	{
		if ((int)obj1->y == (int)obj2->Top() && obj1->y < obj1->Bottom() && obj1->vy > 0)
		{
			obj1->vy = 0;
			return;
		}
		if ((int)obj1->y >= (int)obj2->Top() && (int)obj1->y <= (int)obj2->Top() + 35 && obj1->vy > 0)
		{
			if (!(obj1->Bottom() - obj2->Top() >= 5))
			{
				obj1->y = obj2->Top();
				obj1->vy = 0;
			}
			return;
		}
	}*/

	//Xét va chạm theo phương ngang, bên trái bên phải obj1
	if (nx != 0 && obj2->collType == CollFence)
	{
		//obj1 va chạm phía bên TRÁI obj2
		if (nx == -1.0f)
			obj1->x += obj2->Left() - obj1->Right();
		else //obj1 va chạm phía bên PHẢI obj2, cạnh phải obj2 - cạnh trái obj1 < 0 
			obj1->x += obj2->Right() - obj1->Left();
		obj1->vx = 0;
	}

	//Xét va chạm theo phương dọc, bên trên bên dưới obj1
	if (ny == -1.0f)
	{
		if (obj1->Bottom() - obj2->Top() <= 12)
		{
			obj1->y = obj2->Top();
			obj1->vy = 0;
		}
	}

}

void Collision::CollisionLine(GameObject* obj1, GameObject* obj2, float nx, float ny)
{

	if (obj1->x > obj2->Left() && obj1->x < obj2->Right())
	{
		if ((int)obj1->y == (int)obj2->Top() && obj1->y < obj1->Bottom() && obj1->vy > 0)
		{
			obj1->vy = 0;
			return;
		}
		if ((int)obj1->y >= (int)obj2->Top() && (int)obj1->y <= (int)obj2->Top() + 35 && obj1->vy > 0)
		{
			obj1->y = obj2->Top();
			obj1->vy = 0;
			return;
		}
	}

	if (ny == -1.0f)
	{
		obj1->y += obj2->Top() - obj1->Bottom();
		obj1->vy = 0;
	}
}

Collision::~Collision()
{
}
