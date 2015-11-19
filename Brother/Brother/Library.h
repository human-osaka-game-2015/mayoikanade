#ifndef _LIBRARY_H_
#define _LIBRARY_H_


#include <Windows.h>
#include "SceneManager.h"
#include "D3DManager.h"
#include "DSoundManager.h"
#include "XInput_lib.h"
#include "Texture.h"
#include "Vertex.h"
#include "UVSetter.h"


class Library
{
private:
	D3DManager*		m_pD3DManager;
	DSoundManager*	m_pDSoundManager;
	Texture*		m_pTexture;
	Vertex*			m_pVertex;
	UVSetter*		m_pUVSetter;

public:
	XInput*			m_pXInput;

	Library(HWND hWnd);
	~Library();

	// Dxfont用暫定コード matsumura
	inline LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DManager->pD3Device; }

	// D3DManager
	void Render_Init();
	void Draw_Ready();
	void Draw_End();

	// Texture
	int Tex_Load_EX(const char* name, LPDIRECT3DTEXTURE9* pTexture, int alpha, int red, int green, int blue);

	// Vertex
	void xySet(Position pos, CustomVertex* pVertex);
	void Set_Draw_Tex(LPDIRECT3DTEXTURE9 pTexture, CustomVertex* pVertex);

	// UVSetter
	int FileInfo_Set(const char* name, int fileNum);
	int VertexInfo_Set(const char* name, int vertexNum);
	int AnimaInfo_Set(const char* name, int animaNum);
	void FileInfo_Release();
	void VertexInfo_Release();
	void AnimaInfo_Release();
	void MakePosition(int vertexNum, Position* pPos);
	void MakeVertex(int vertexNum, CustomVertex* pVertex);
	void InitAnima(int animaNum);
	int AnimaControl(int animaNum);
	void UVReversal(CustomVertex* pVertex, REVERSAL_NUM rev);

	// XInput
	void Check(XINPUTPAD pad);
	PADSTATE GetButtonState(XINPUT_ID id, XINPUTPAD pad);
	bool GetAnalogState(ANALOGPAD id, XINPUTPAD pad);
};


#endif