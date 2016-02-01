#include "GameMain.h"
#include "SceneManager.h"
#include "Library.h"



/**
 * GameMain�N���X�̃R���X�g���N�^
 * @param[in] hWnd		�E�B���h�E�n���h��
 */
GameMain::GameMain(HWND hWnd)
{
	m_pLibrary = new Library(hWnd, false,true);
	m_pSceneManager = new SceneManager(m_pLibrary,hWnd);
}

/**
 * GameMain�N���X�̃f�X�g���N�^
 */
GameMain::~GameMain()
{
	delete m_pSceneManager;
	delete m_pLibrary;
}
