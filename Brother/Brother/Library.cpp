#include "Library.h"


Library::Library(HWND hWnd):m_pD3DManager(NULL), m_pDSoundManager(NULL), m_pXInput(NULL), m_pTexture(NULL), m_pVertex(NULL), m_pUVSetter(NULL), m_hWnd(hWnd)
{
	m_pD3DManager = new D3DManager(m_hWnd);
	m_pDSoundManager = new DSoundManager(m_hWnd);
	m_pXInput = new XInput();
	m_pTexture = new Texture();
	m_pVertex = new Vertex();
	m_pUVSetter = new UVSetter();
}

Library::~Library()
{
	delete m_pUVSetter;
	delete m_pVertex;
	delete m_pTexture;
	delete m_pXInput;
	delete m_pDSoundManager;
	delete m_pD3DManager;
}