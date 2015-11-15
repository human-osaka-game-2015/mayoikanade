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

public:
	Library(HWND hWnd);
	~Library();
	HWND m_hWnd;
	D3DManager*		m_pD3DManager;
	DSoundManager*	m_pDSoundManager;
	XInput*			m_pXInput;
	Texture*		m_pTexture;
	Vertex*			m_pVertex;
	UVSetter*		m_pUVSetter;

};


#endif