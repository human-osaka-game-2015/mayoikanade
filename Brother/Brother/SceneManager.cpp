#include "SceneManager.h"
#include "LogoScene.h"
#include "OpeningScene.h"
#include "TitleScene.h"
#include "ConnectingScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Library.h"

SceneManager::SceneManager(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{
	//αは仮でGameSceneをnewするが、ふつうはLogoScene
	m_pScene = new GameScene(m_pLibrary);

	//SetRenderStateを先にしとく
	m_pLibrary->m_pD3DManager->Render_Init();


	

}

SceneManager::~SceneManager()
{
	delete m_pScene;
}

void SceneManager::Control()
{
	
	switch (m_NextScene)
	{
	case SCENE_NONE:
		//そのまま抜ける
		break;
	case LOGO_SCENE:
		delete m_pScene;
		m_pScene = new LogoScene(m_pLibrary);

		break;
	case OPENING_SCENE:
		delete m_pScene;
		m_pScene = new OpeningScene(m_pLibrary);

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
		m_pScene = new GameScene(m_pLibrary);

		break;
	case RESULT_SCENE:
		delete m_pScene;
		m_pScene = new ResultScene(m_pLibrary);

		break;
	default:
		//例外
		MessageBox(0, "m_NextSceneに予期していない数値が入っています。", "", MB_OK);
		break;
	}

	m_NextScene = m_pScene->Control();

}

void SceneManager::Draw()
{
	m_pScene->Draw();
}