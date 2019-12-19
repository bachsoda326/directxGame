#pragma once
#include <vector>
#include "Aladdin.h"
#include "debug.h"

/*
Grid có chiều dài, rộng = map và gồm nhiều cell, mỗi cell chứa 1 listObj
*/

struct Cell
{
	std::vector<GameObject*> listObj;
};

class Grid
{
public:
	// dài, rộng của grid
	int width, height;
	// độ lớn của mỗi cell trong grid
	int cellSize;
	std::vector<Cell> listCells;
	// số cell theo chiều ngang grid
	int numXCells;
	// số cell theo chiều rộng grid
	int numYCells;

public:
	Grid(int width, int height, int cellSize);
	~Grid();

	// Thêm obj vào listObjs của cell thích hợp
	void AddObjToCell(GameObject * obj);
	void AddObjToCell(int cellIndex, GameObject * obj);

	// Get Cell dựa trên vị trí của cell
	Cell& GetCell(int x, int y);
	// Get Cell dựa trên vị trí của obj
	Cell& GetCell(D3DXVECTOR3& posObj);

	// Tính toán các obj có thể bị va chạm (Tính toán các cell cần đc update với vị trí của camera)
	void CalcColliableObjs(Camera *camera, vector<LPGAMEOBJECT>& coObjs);
};

