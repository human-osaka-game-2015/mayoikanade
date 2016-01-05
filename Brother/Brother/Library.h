#ifndef LIBRARY_H
#define LIBRARY_H


#include <Windows.h>
#include "SceneManager.h"
#include "DSoundManager.h"
#include "XInput_lib.h"
#include "Texture.h"
#include "Vertex.h"
#include "UVSetter.h"
#include "StencilManager.h"
#include "InputDevice.h"

class D3DManager;

class Library
{
private:
	D3DManager*		m_pD3DManager;
	DSoundManager*	m_pDSoundManager;
	Texture*		m_pTexture;
	Vertex*			m_pVertex;
	UVSetter*		m_pUVSetter;
	XInput*			m_pXInput;
	StencilManager*	m_pStencilManager;
	InputDevice* m_pInputDevice;


public:
	Library(HWND hWnd, bool isFullWindow = false, bool isStencil = false);
	~Library();

	//DXFontÇçÏÇÈÇ‹Ç≈ÇÃä÷êî
	LPDIRECT3DDEVICE9 GetDevice();

	void SetTexture(int key);
	void DrawTexture(int key, CustomVertex* pVertex);

	// D3DManager
	void Render_Init();
	void Draw_Ready();
	void Draw_End();

	//DSoundManager
	int SoundLoad(char* filename, int Key);
	void SoundRelease(int Key);
	void Sound_Operation(int Key, SOUND_OPERATION operation);

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

	//StencilManager
	void StencilDrawReady();
	void StencilDrawEnd();
	void StencilRefSet(BYTE ref);
	void StencilDraw(CustomVertex* vertex);
	void AlphaTestReady(BYTE ref);
	void AlphaTestEnd();
	void StencilTestEnd();


	//StencilManager
	HRESULT InitDinputKey();
	HRESULT InitDinputMouse();
	void KeyCheck(KEYSTATE* Key, int DIK);
	void MouseCheck(MOUSEKIND* Mouse);

};


#endif