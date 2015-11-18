#include "Library.h"


Library::Library(HWND hWnd):m_pD3DManager(NULL), m_pDSoundManager(NULL), m_pXInput(NULL), m_pTexture(NULL), m_pVertex(NULL), m_pUVSetter(NULL)
{
	m_pD3DManager = new D3DManager(hWnd);
	m_pDSoundManager = new DSoundManager(hWnd);
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

void Library::Render_Init()
{
	m_pD3DManager->Render_Init();
}

void Library::Draw_Ready()
{
	m_pD3DManager->Draw_Ready();
}

void Library::Draw_End()
{
	m_pD3DManager->Draw_End();
}

int Library::Tex_Load_EX(const char* name, LPDIRECT3DTEXTURE9* pTexture, int alpha, int red, int green, int blue)
{
	return m_pTexture->Tex_Load_EX(name, pTexture, alpha, red, green, blue);
}

void Library::xySet(Position pos, CustomVertex* pVertex)
{
	m_pVertex->xySet(pos, pVertex);
}

void Library::Set_Draw_Tex(LPDIRECT3DTEXTURE9 pTexture, CustomVertex* pVertex)
{
	m_pVertex->Set_Draw_Tex(pTexture, pVertex);
}

int Library::FileInfo_Set(const char* name, int fileNum)
{
	return m_pUVSetter->FileInfo_Set(name, fileNum);
}

int Library::VertexInfo_Set(const char* name, int vertexNum)
{
	return m_pUVSetter->VertexInfo_Set(name, vertexNum);
}

int Library::AnimaInfo_Set(const char* name, int animaNum)
{
	return m_pUVSetter->AnimaInfo_Set(name, animaNum);
}

void Library::FileInfo_Release()
{
	m_pUVSetter->FileInfo_Release();
}

void Library::VertexInfo_Release()
{
	m_pUVSetter->VertexInfo_Release();
}

void Library::AnimaInfo_Release()
{
	m_pUVSetter->AnimaInfo_Release();
}

void Library::MakePosition(int vertexNum, Position* pPos)
{
	m_pUVSetter->MakePosition(vertexNum, pPos);
}

void Library::MakeVertex(int vertexNum, CustomVertex* pVertex)
{
	m_pUVSetter->MakeVertex(vertexNum, pVertex);
}

void Library::InitAnima(int animaNum)
{
	m_pUVSetter->InitAnima(animaNum);
}

int Library::AnimaControl(int animaNum)
{
	return m_pUVSetter->AnimaControl(animaNum);
}

void Library::UVReversal(CustomVertex* pVertex, REVERSAL_NUM rev)
{
	m_pUVSetter->UVReversal(pVertex, rev);
}
