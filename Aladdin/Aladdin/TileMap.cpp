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
	// tạo texture map
	Textures::GetInstance()->Add(id, texMapPath, D3DCOLOR_XRGB(255, 255, 255));

	fstream fs;
	fs.open(txtMapPath);

	fs >> numXTiles;
	fs >> numYTiles;
	// đặt lại size cho listTiles
	listTiles.resize(numXTiles*numYTiles);
	// set các tile = các số trong file
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
		// tạo sprite tương ứng vs các tile từ texture map
		sprite = new Sprite(i, left, top, 32, 32, 0, 0, texture);
		listSprites.push_back(sprite);
	}
}

void TileMap::Render(Camera *camera)
{	
	// tính vị trí topleft và botright của camera
	int xTopLeftCamera = camera->GetPosition().x - SCREEN_WIDTH / 2;
	int yTopLeftCamera = camera->GetPosition().y - SCREEN_HEIGHT / 2;
	int xBotRightCamera = camera->GetPosition().x + SCREEN_WIDTH / 2;
	int yBotRightCamera = camera->GetPosition().y + SCREEN_HEIGHT / 2;
	// tính vị trí topleft và botright của cell
	int xTopLeftCell = xTopLeftCamera / CELL_SIZE;
	int yTopLeftCell = yTopLeftCamera / CELL_SIZE;
	int xBotRightCell = xBotRightCamera / CELL_SIZE;
	int yBotRightCell = yBotRightCamera / CELL_SIZE;
	// tính vị trí topleft và botright của tile
	int xTopLeft = xTopLeftCell * CELL_SIZE / 32;
	int yTopLeft = yTopLeftCell * CELL_SIZE / 32;
	int xBotRight = ((xBotRightCell * CELL_SIZE) + CELL_SIZE) / 32;
	int yBotRight = ((yBotRightCell * CELL_SIZE) + CELL_SIZE) / 32;
	if (xBotRight >= numXTiles - 1)
		xBotRight = numXTiles - 1;
	if (yBotRight >= numYTiles - 1)
		yBotRight = numYTiles - 1;

	for (int x = xTopLeft; x <= xBotRight; x++)
	{
		for (int y = yTopLeft; y <= yBotRight; y++)
		{
			int xDrawIndex, yDrawIndex, xDraw, yDraw, i;
			i = x + y * numXTiles;
			yDrawIndex = i / numXTiles;
			xDrawIndex = i - yDrawIndex * numXTiles;
			xDraw = xDrawIndex * 32;
			yDraw = yDrawIndex * 32;

			D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
			listSprites[i]->Draw(xDraw, yDraw, trans);
		}
	}

	/*int xDrawIndex, yDrawIndex, xDraw, yDraw;
		
	for (int i = 0; i < listSprites.size(); i++)
	{		
		yDrawIndex = i / numXTiles;
		xDrawIndex = i - yDrawIndex*numXTiles;
		xDraw = xDrawIndex * 32;
		yDraw = yDrawIndex * 32;
		D3DXVECTOR2 trans = D3DXVECTOR2(floor(SCREEN_WIDTH / 2 - Camera::GetInstance()->GetPosition().x), floor(SCREEN_HEIGHT / 2 - Camera::GetInstance()->GetPosition().y));
		listSprites[i]->Draw(xDraw, yDraw, trans);
	}*/
}
