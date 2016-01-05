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
#include "Vertex.h"
#include "Texture.h"





Texture::Texture()
{

}

Texture::~Texture()
{

}


int Texture::LoadTexture(const char* name, int key)
{
	LPDIRECT3DTEXTURE9 pTexture;

	if (FAILED(D3DXCreateTextureFromFile(
		D3DManager::pD3Device,
		TEXT(name),
		&pTexture)))
	{
		MessageBox(0, "テクスチャの読み込みに失敗しました", name, MB_OK);
		return -1;
	}

	m_textureMap[key] = pTexture;

	return 0;
}


int Texture::LoadTextureEx(const char* name, int key, int alpha, int red, int green, int blue)
{
	LPDIRECT3DTEXTURE9 pTexture;

	if(FAILED(D3DXCreateTextureFromFileEx(
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
		D3DCOLOR_ARGB(alpha, red, green, blue),
		NULL, NULL,
		&pTexture)))
	{
		return 1;
	}

	m_textureMap[key] = pTexture;

	return 0;
}


void Texture::ReleaseTexture(int key)
{
	m_textureMap[key]->Release();
	m_textureMap.erase(key);
}


void Texture::SetTexture(int key)
{
	D3DManager::pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);
	D3DManager::pD3Device->SetTexture(0, m_textureMap[key]);
}


void Texture::DrawTexture(int key, CustomVertex* pVertex)
{
	SetTexture(key);
	D3DManager::pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, pVertex, sizeof(CustomVertex));
}



