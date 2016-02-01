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
#include "Vertex.h"
#include "Texture.h"



/**
 * Textureクラスのコンストラクタ
 */
Texture::Texture(LPDIRECT3DDEVICE9 pDevice):
m_pDevice(pDevice)
{

}

/**
 * Textureクラスのデストラクタ
 */
Texture::~Texture()
{

}


/**
 * テクスチャの読み込み
 * @param[in] name 読み込むファイルの名前
 * @param[in] key 格納先のキー
 * @return 成功したかどうかの情報
 */
int Texture::LoadTexture(const char* name, int key)
{
	LPDIRECT3DTEXTURE9 pTexture;

	if (FAILED(D3DXCreateTextureFromFile(
		m_pDevice,
		TEXT(name),
		&pTexture)))
	{
		MessageBox(0, "テクスチャの読み込みに失敗しました", name, MB_OK);
		return -1;
	}

	m_textureMap[key] = pTexture;

	return 0;
}

/**
 * テクスチャの読み込み
 * @param[in] name 読み込むファイルの名前
 * @param[in] key 格納先のキー
 * @param[in] alpha 透過する色の指定(α)
 * @param[in] red 透過する色の指定(赤)
 * @param[in] green 透過する色の指定(緑)
 * @param[in] blue 透過する色の指定(青)
 * @return 成功したかどうかの情報
 */
int Texture::LoadTextureEx(const char* name, int key, int alpha, int red, int green, int blue)
{
	LPDIRECT3DTEXTURE9 pTexture;

	if(FAILED(D3DXCreateTextureFromFileEx(
		m_pDevice,
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

/**
 * テクスチャの解放
 * @param[in] key 解放する画像の格納先のキー
 */
void Texture::ReleaseTexture(int key)
{
	m_textureMap[key]->Release();
	m_textureMap.erase(key);
}

/**
 * テクスチャをステージに割り当てる
 * @param[in] key 格納先キー
 */
void Texture::SetTexture(int key)
{
	m_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pDevice->SetTexture(0, m_textureMap[key]);
}

/**
 * 描画関数
 * @param[in] key 描画するテクスチャの格納先キー
 * @param[in] pVertex 描画する頂点座標
 */
void Texture::DrawTexture(int key, CustomVertex* pVertex)
{
	SetTexture(key);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, pVertex, sizeof(CustomVertex));
}



