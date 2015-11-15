/**
 * @file Texture.cpp
 * @brief Textureクラス
 * @author 森本
 * @date 11月9日
 */

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <mmsystem.h>
#include "D3DManager.h"
#include"Texture.h"




Texture::Texture()
{

}

Texture::~Texture()
{

}


/**
 * Textureをロードする関数
 * D3DXCreateTextureFromFileExを使ってロードする
 * const char*が画像のファイル名
 * Lm_pDirect3DTEXTURE9* は画像を保存する場所のアドレス
 */
int Texture::Tex_Load_EX(const char* name, LPDIRECT3DTEXTURE9* pTexture, int alpha = 255, int red = 0, int grren = 255, int blue = 0)
{
	
	if (FAILED(D3DXCreateTextureFromFileEx(
		D3DManager::pD3Device,
		TEXT(name),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		D3DCOLOR_ARGB(alpha, red, grren, blue),
		NULL, NULL,
		pTexture)))
	{
		return 1;
	}
	return 0;
}

int Texture::Tex_Load(const char* name, LPDIRECT3DTEXTURE9* pTexture)
{
	if (FAILED(D3DXCreateTextureFromFile(
		D3DManager::pD3Device,
		TEXT(name),
		pTexture)))
	{
		MessageBox(0, "テクスチャの読み込みに失敗しました", name, MB_OK);
		return -1;
	}
	return 0;
}


