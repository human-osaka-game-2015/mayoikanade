#ifndef LIBRARY_H
#define LIBRARY_H


#include <Windows.h>
#include "DSoundManager.h"
#include "Texture.h"
#include "Vertex.h"
#include "UVSetter.h"
#include "XInput.h"
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
	InputDevice*	m_pInputDevice;


public:
	Library(HWND hWnd, bool isFullWindow = false, bool isStencil = false);
	~Library();

	//DXFontÇçÏÇÈÇ‹Ç≈ÇÃä÷êî
	LPDIRECT3DDEVICE9 GetDevice();


	
	// D3DManager
	void RenderInit();
	void DrawReady();
	void DrawEnd();

	//DSoundManager
	int SoundLoad(char* filename, int Key);
	void ReleaseSound(int Key);
	void SoundOperation(int Key, SOUND_OPERATION operation);

	// Texture
	int LoadTextureEx(const char* name, int key, int alpha, int red, int green, int blue);
	void ReleaseTexture(int key);
	void DrawTexture(int key, CustomVertex* pVertex);


	// Vertex
	void xySet(Position pos, CustomVertex* pVertex);
	void Library::Turn(CustomVertex* pVertex, Position* pos, double angle);

	// UVSetter
	int FileInfoSet(const char* name, int fileNum);
	int VertexInfoSet(const char* name, int vertexNum);
	int AnimaInfoSet(const char* name, int animaNum);
	void FileInfoRelease();
	void VertexInfoRelease();
	void AnimaInfoRelease();
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