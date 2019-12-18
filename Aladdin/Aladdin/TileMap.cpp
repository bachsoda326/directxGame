#include "TileMap.h"

TileMap::TileMap()
{
}


TileMap::~TileMap()
{
}

void TileMap::LoadTileMap(int id, LPCSTR texMapPath, string txtMapPath)
{	
	this->id = id;
	Textures::GetInstance()->Add(id, texMapPath, D3DCOLOR_XRGB(255, 255, 255));

	fstream fs;
	fs.open(txtMapPath);

	fs >> numXTiles;
	fs >> numYTiles;

	listTiles.resize(numXTiles*numYTiles);

	for (int i = 0; i < listTiles.size(); i++)
	{
		fs >> listTiles[i];		
	}

	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(id);
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	int numColumns = desc.Width / 32;	// 32
	//int numRows = desc.Height / 32;	// 76	

	LPSPRITE sprite;
	int tileIndex;
	int xIndex, yIndex, left, top;
	int xDrawIndex, yDrawIndex, xDraw, yDraw;

	for (int i = 0; i < listTiles.size(); i++)
	{
		tileIndex = listTiles[i];
		yIndex = tileIndex / numColumns;
		xIndex = tileIndex - yIndex * numColumns;
		left = xIndex * 32;
		top = yIndex * 32;
		sprite = new Sprite(i, left, top, 32, 32, 0, 0, texture);
		listSprites.push_back(sprite);
	}
}

void TileMap::Render()
{	
	int xDrawIndex, yDrawIndex, xDraw, yDraw;
		
	for (int i = 0; i < listSprites.size(); i++)
	{		
		yDrawIndex = i / numXTiles;
		xDrawIndex = i - yDrawIndex*numXTiles;
		xDraw = xDrawIndex * 32;
		yDraw = yDrawIndex * 32;
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		listSprites[i]->Draw(xDraw, yDraw, trans);
	}
}
