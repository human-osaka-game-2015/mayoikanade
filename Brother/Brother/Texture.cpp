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
#include "Vertex.h"
#include "Texture.h"



/**
 * Texture�N���X�̃R���X�g���N�^
 */
Texture::Texture(LPDIRECT3DDEVICE9 pDevice):
m_pDevice(pDevice)
{

}

/**
 * Texture�N���X�̃f�X�g���N�^
 */
Texture::~Texture()
{

}


/**
 * �e�N�X�`���̓ǂݍ���
 * @param[in] name �ǂݍ��ރt�@�C���̖��O
 * @param[in] key �i�[��̃L�[
 * @return �����������ǂ����̏��
 */
int Texture::LoadTexture(const char* name, int key)
{
	LPDIRECT3DTEXTURE9 pTexture;

	if (FAILED(D3DXCreateTextureFromFile(
		m_pDevice,
		TEXT(name),
		&pTexture)))
	{
		MessageBox(0, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", name, MB_OK);
		return -1;
	}

	m_textureMap[key] = pTexture;

	return 0;
}

/**
 * �e�N�X�`���̓ǂݍ���
 * @param[in] name �ǂݍ��ރt�@�C���̖��O
 * @param[in] key �i�[��̃L�[
 * @param[in] alpha ���߂���F�̎w��(��)
 * @param[in] red ���߂���F�̎w��(��)
 * @param[in] green ���߂���F�̎w��(��)
 * @param[in] blue ���߂���F�̎w��(��)
 * @return �����������ǂ����̏��
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
 * �e�N�X�`���̉��
 * @param[in] key �������摜�̊i�[��̃L�[
 */
void Texture::ReleaseTexture(int key)
{
	m_textureMap[key]->Release();
	m_textureMap.erase(key);
}

/**
 * �e�N�X�`�����X�e�[�W�Ɋ��蓖�Ă�
 * @param[in] key �i�[��L�[
 */
void Texture::SetTexture(int key)
{
	m_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pDevice->SetTexture(0, m_textureMap[key]);
}

/**
 * �`��֐�
 * @param[in] key �`�悷��e�N�X�`���̊i�[��L�[
 * @param[in] pVertex �`�悷�钸�_���W
 */
void Texture::DrawTexture(int key, CustomVertex* pVertex)
{
	SetTexture(key);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, pVertex, sizeof(CustomVertex));
}



