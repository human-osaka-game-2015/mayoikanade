#include "GameMain.h"
#include "SceneManager.h"
#include "Library.h"



/**
 * GameMainクラスのコンストラクタ
 * @param[in] hWnd		ウィンドウハンドル
 */
GameMain::GameMain(HWND hWnd)
{
	m_pLibrary = new Library(hWnd, false,true);
	m_pSceneManager = new SceneManager(m_pLibrary,hWnd);
}

/**
 * GameMainクラスのデストラクタ
 */
GameMain::~GameMain()
{
	delete m_pSceneManager;
	delete m_pLibrary;
}
