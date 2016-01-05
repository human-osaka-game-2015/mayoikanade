/**
* @file Library.cpp
* @brief Libraryクラス
* @author 森本
* @date 12月9日
*/
#include "D3DManager.h"
#include "Library.h"




Library::Library(HWND hWnd, bool isFullWindow,bool isStencil) :m_pD3DManager(NULL), m_pDSoundManager(NULL), m_pXInput(NULL), m_pTexture(NULL), m_pVertex(NULL), m_pUVSetter(NULL)
{
	m_pD3DManager = new D3DManager(hWnd, isFullWindow,isStencil);
	m_pDSoundManager = new DSoundManager(hWnd);
	m_pXInput = new XInput();
	m_pTexture = new Texture();
	m_pVertex = new Vertex();
	m_pUVSetter = new UVSetter();
	m_pStencilManager = new StencilManager();
	m_pInputDevice = new InputDevice(hWnd);
}


Library::~Library()
{
	delete m_pInputDevice;
	delete m_pStencilManager;
	delete m_pUVSetter;
	delete m_pVertex;
	delete m_pTexture;
	delete m_pXInput;
	delete m_pDSoundManager;
	delete m_pD3DManager;
}







//DFont生成用に作ったやつなんでそのうち消す
LPDIRECT3DDEVICE9 Library::GetDevice()
{
	return m_pD3DManager->pD3Device;
}



//--------------------------------------------------------------------------------------
//
//		D3DManager
//
//--------------------------------------------------------------------------------------
void Library::RenderInit()
{
	m_pD3DManager->RenderInit();
}


void Library::DrawReady()
{
	m_pD3DManager->DrawReady();
}


void Library::DrawEnd()
{
	m_pD3DManager->DrawEnd();
}



//--------------------------------------------------------------------------------------
//
//		DSoundManager
//
//--------------------------------------------------------------------------------------
int Library::SoundLoad(char* filename, int Key)
{
	return m_pDSoundManager->SoundLoad(filename, Key);
}


void Library::ReleaseSound(int Key)
{
	m_pDSoundManager->ReleaseSound(Key);
}


void Library::SoundOperation(int Key, SOUND_OPERATION operation)
{
	m_pDSoundManager->SoundOperation(Key, operation);
}


//--------------------------------------------------------------------------------------
//
//		Texture
//
//--------------------------------------------------------------------------------------
int Library::LoadTextureEx(const char* name, int key, int alpha = 255, int red = 0, int green = 255, int blue = 0)
{
	return m_pTexture->LoadTextureEx(name, key, alpha, red, green, blue);
}


void Library::ReleaseTexture(int key)
{
	m_pTexture->ReleaseTexture(key);
}

void Library::DrawTexture(int key, CustomVertex* pVertex)
{
	m_pTexture->DrawTexture(key, pVertex);
}



//--------------------------------------------------------------------------------------
//
//		Vertex
//
//--------------------------------------------------------------------------------------
void Library::xySet(Position pos, CustomVertex* pVertex)
{
	m_pVertex->xySet(pos, pVertex);
}



//--------------------------------------------------------------------------------------
//
//		UVSetter
//
//--------------------------------------------------------------------------------------
int Library::FileInfoSet(const char* name, int fileNum)
{
	return m_pUVSetter->FileInfoSet(name, fileNum);
}


int Library::VertexInfoSet(const char* name, int vertexNum)
{
	return m_pUVSetter->VertexInfoSet(name, vertexNum);
}


int Library::AnimaInfoSet(const char* name, int animaNum)
{
	return m_pUVSetter->AnimaInfoSet(name, animaNum);
}


void Library::FileInfoRelease()
{
	m_pUVSetter->FileInfoRelease();
}


void Library::VertexInfoRelease()
{
	m_pUVSetter->VertexInfoRelease();
}


void Library::AnimaInfoRelease()
{
	m_pUVSetter->AnimaInfoRelease();
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


//--------------------------------------------------------------------------------------
//
//		XInput
//
//--------------------------------------------------------------------------------------
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



//--------------------------------------------------------------------------------------
//
//		StencilManager
//
//--------------------------------------------------------------------------------------
void Library::StencilDrawReady()
{
	m_pStencilManager->StencilDrawReady();
}


void Library::StencilDrawEnd()
{
	m_pStencilManager->StencilDrawEnd();
}


void Library::StencilRefSet(BYTE ref)
{
	m_pStencilManager->StencilRefSet(ref);
}


void Library::StencilDraw(CustomVertex* vertex)
{
	m_pStencilManager->StencilDraw(vertex);
}


void Library::AlphaTestReady(BYTE ref)
{
	m_pStencilManager->AlphaTestReady(ref);
}


void Library::AlphaTestEnd()
{
	m_pStencilManager->AlphaTestEnd();
}


void Library::StencilTestEnd()
{
	m_pStencilManager->StencilTestEnd();
}



//--------------------------------------------------------------------------------------
//
//		InputDevice
//
//--------------------------------------------------------------------------------------
HRESULT Library::InitDinputKey()
{
	return m_pInputDevice->InitDinputKey();
}


HRESULT Library::InitDinputMouse()
{
	return m_pInputDevice->InitDinputMouse();
}


void Library::KeyCheck(KEYSTATE* Key, int DIK)
{
	m_pInputDevice->KeyCheck(Key, DIK);
}


void Library::MouseCheck(MOUSEKIND* Mouse)
{
	m_pInputDevice->MouseCheck(Mouse);
}





