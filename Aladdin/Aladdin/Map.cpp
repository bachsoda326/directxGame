#include "Map.h"



Map::Map(int idMap)
{
	sprite = Sprites::GetInstance()->Get(idMap);
}

Map::~Map()
{
}

//void Map::SetCamera(Camera * camera)
//{
//	this->camera = camera;
//}

void Map::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt);
}

void Map::Render()
{	
	if (true)
	{
		// Vector trans giúp dời ảnh theo camera
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		sprite->Draw(x, y, trans);
	}
	else
		sprite->Draw(x, y, D3DXVECTOR2(0, 0));
}