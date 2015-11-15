/**
 * @file Texture.cpp
 * @brief Texture�N���X
 * @author �X�{
 * @date 11��9��
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
 * Texture�����[�h����֐�
 * D3DXCreateTextureFromFileEx���g���ă��[�h����
 * const char*���摜�̃t�@�C����
 * Lm_pDirect3DTEXTURE9* �͉摜��ۑ�����ꏊ�̃A�h���X
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
		MessageBox(0, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", name, MB_OK);
		return -1;
	}
	return 0;
}


