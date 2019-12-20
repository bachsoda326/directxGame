#pragma once
#include <vector>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include "Constants.h"
#include "Camera.h"
#include <fstream>
#include "Textures.h"
#include "Sprites.h"
#include "debug.h"

using namespace std;

class TileMap
{
private:
	// listTiles (list chứa các số trong file mapTile)
	std::vector<int> listTiles;
	// listSprites (ảnh) tương ứng vs các tiles
	std::vector<LPSPRITE> listSprites;
	// số tiles theo chiều ngang
	int numXTiles;
	// số tiles theo chiều dọc
	int numYTiles;
	// id để tạo texture map
	int id;

public:
	TileMap();
	~TileMap();

	void LoadTileMap(int id, LPCSTR texMapPath, string txtMapPath);
	void Render(Camera *camera);
};

