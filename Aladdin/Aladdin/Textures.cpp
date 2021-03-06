﻿#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "textures.h"

Textures * Textures::__instance = NULL;

Textures::Textures()
{

}

Textures *Textures::GetInstance()
{
	if (__instance == NULL) __instance = new Textures();
	return __instance;
}

void Textures::Add(int id, LPCSTR filePath, D3DCOLOR transparentColor)
{
	// thông tin ảnh
	D3DXIMAGE_INFO info;
	// lấy thông tin ảnh từ file
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut("[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}
	width = info.Width;
	height = info.Height;

	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;
	// tạo texture từ thông tin đã có
	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString("[ERROR] CreateTextureFromFile failed\n");
		return;
	}
	textures[id] = texture;

	DebugOut("[INFO] Texture loaded Ok: id=%d, %s \n", id, filePath);
}

LPDIRECT3DTEXTURE9 Textures::Get(unsigned int i)
{
	return textures[i];
}