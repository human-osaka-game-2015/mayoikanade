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

void Library::SetTexture(int key)
{
	//‰æ‘œ‚Ì•`‰æ
	D3DManager::pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pTexture->SetTexture(key);
}

void Library::DrawTexture(int key, CustomVertex* pVertex)
{
	SetTexture(key);
	D3DManager::pD3Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		pVertex,
		sizeof(CustomVertex));
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

int Library::LoadTextureEx(const char* name, int key, int alpha = 255, int red = 0, int green = 255, int blue = 0)
{
	return m_pTexture->LoadEx(name, key, alpha, red, green, blue);
}

void Library::ReleaseTexture(int key)
{
	m_pTexture->Release(key);
}

void Library::xySet(Position pos, CustomVertex* pVertex)
{
	m_pVertex->xySet(pos, pVertex);
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

void Library::Check(XINPUTPAD pad)
{
	m_pXInput->Check(pad);
}

PADSTATE Library::GetButtonState(XINPUT_ID id, XINPUTPAD pad)
{
	return m_pXInput->GetButtonState(id, pad);
}

bool Library::GetAnalogState(ANALOGPAD id, XINPUTPAD pad)
{
	return m_pXInput->GetAnalogState(id, pad);
}
