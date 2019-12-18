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
public:
	TileMap();
	~TileMap();

	void LoadTileMap(int id, LPCSTR texMapPath, string txtMapPath);
	void Render();

private:		
	std::vector<int> listTiles;
	std::vector<LPSPRITE> listSprites;
	int numXTiles, numYTiles;
	int id;
};

