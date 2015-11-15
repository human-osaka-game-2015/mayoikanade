#include "GameMain.h"
#include "SceneManager.h"
#include "Library.h"

GameMain::GameMain(HWND hWnd)
{
	m_pLibrary = new Library(hWnd);
	m_pSceneManager = new SceneManager(m_pLibrary);
	
}

GameMain::~GameMain()
{
	delete m_pSceneManager;
	delete m_pLibrary;
}
