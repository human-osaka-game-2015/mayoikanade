#include "SceneManager.h"
#include "Scene.h"
#include "LogoScene.h"
#include "OpeningScene.h"
#include "TitleScene.h"
#include "ConnectingScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "StaffScene.h"
#include "Library.h"



SceneManager::SceneManager(Library* pLibrary,HWND hWnd) :
m_pLibrary(pLibrary), 
m_NextScene(SCENE_NONE),
m_hWnd(hWnd)
{
	//�Q�[���̊J�n���̃V�[���̓��S�ɍs��
	m_pScene = new LogoScene(m_pLibrary);

	//SetRenderState���̏���
	m_pLibrary->Render_Init();

}

SceneManager::~SceneManager()
{
	delete m_pScene;
}

bool SceneManager::Control()
{
	
	switch (m_NextScene)
	{
	case SCENE_NONE:	//���̂܂ܔ�����

		break;
	case LOGO_SCENE:
		delete m_pScene;
		m_pScene = new LogoScene(m_pLibrary);

		break;
	case OPENING_SCENE:
		delete m_pScene;
		m_pScene = new OpeningScene(m_pLibrary,m_hWnd);

		break;
	case TITLE_SCENE:
		delete m_pScene;
		m_pScene = new TitleScene(m_pLibrary);

		break;
	case CONNECTING_SCENE:
		delete m_pScene;
		m_pScene = new ConnectingScene(m_pLibrary);

		break;
	case GAME_SCENE:
		delete m_pScene;
		m_pScene = new GameScene(m_pLibrary, m_hWnd);

		break;
	case RESULT_SCENE:
		delete m_pScene;
		m_pScene = new ResultScene(m_pLibrary);

		break;
	case STAFF_SCENE:
		delete m_pScene;
		m_pScene = new StaffScene(m_pLibrary);

		break;
	case END_SCENE:		//true��Ԃ��ăQ�[�����I������
		return true;
		break;
	default:
		MessageBox(0, "m_NextScene�ɗ\�����Ă��Ȃ����l�������Ă��܂��B", "", MB_OK);
		break;
	}

	m_NextScene = m_pScene->Control();
	
	return false;
}

void SceneManager::Draw()
{
	m_pLibrary->Draw_Ready();

	m_pScene->Draw();

	m_pLibrary->Draw_End();

}