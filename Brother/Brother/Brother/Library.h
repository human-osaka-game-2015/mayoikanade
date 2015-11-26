#ifndef LIBRARY_H
#define LIBRARY_H


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
	XInput*			m_pXInput;

public:
	Library(HWND hWnd,bool isFullWindow=false);
	~Library();

	// Dxfont用暫定コード matsumura
	inline LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DManager->pD3Device; }

	void SetTexture(int key);
	void DrawTexture(int key, CustomVertex* pVertex);

	// D3DManager
	void Render_Init();
	void Draw_Ready();
	void Draw_End();

	// Texture
	int LoadTextureEx(const char* name, int key, int alpha, int red, int green, int blue);
	void ReleaseTexture(int key);

	// Vertex
	void xySet(Position pos, CustomVertex* pVertex);

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