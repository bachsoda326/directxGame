#pragma once
#include <unordered_map>
#include <d3dx9.h>

using namespace std;

/*
Manage texture database
*/
class CTextures
{
	static CTextures * __instance;
	// kiểu như listTextures
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:
	CTextures();
	// Add texture vào instance"textures"
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	// Get texture theo id trong instance"textures"
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	static CTextures * GetInstance();
};