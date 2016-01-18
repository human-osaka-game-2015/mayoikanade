#include "SceneManager.h"
#include "Scene.h"
#include "LogoScene.h"
#include "OpeningScene.h"
#include "TitleScene.h"
#include "ConnectingScene.h"
#include "ServerGameScene.h"
#include "ClientGameScene.h"
#include "ResultScene.h"
#include "StaffScene.h"
#include "Library.h"

SceneManager::SceneManager(Library* pLibrary,HWND hWnd) :
m_pLibrary(pLibrary), 
m_NextScene(SCENE_NONE),
m_hWnd(hWnd)
{
	//ゲームの開始時のシーンはロゴに行く
	m_pScene = new LogoScene(m_pLibrary);

	//SetRenderState等の処理
	m_pLibrary->RenderInit();
}

SceneManager::~SceneManager()
{
	delete m_pScene;
}

bool SceneManager::Control()
{
	//サーバーかクライアントの切り替えはこのシーンで分ける
	switch (m_NextScene)
	{
	case SCENE_NONE:	//そのまま抜ける

		break;
	case LOGO_SCENE:
		delete m_pScene;
		m_pScene = new LogoScene(m_pLibrary);
		break;
	case OPENING_SCENE:
		delete m_pScene;
		m_pScene = new OpeningScene(m_pLibrary, m_hWnd);
		break;
	case TITLE_SCENE:
		delete m_pScene;
		m_pScene = new TitleScene(m_pLibrary);
		break;
	case CONNECTING_SCENE:
		delete m_pScene;
		m_pScene = new ConnectingScene(m_pLibrary, m_pIPadd);
		break;
	case SERVER_GAME_SCENE:
		delete m_pScene;
		m_pScene = new ServerGameScene(m_pLibrary, m_hWnd, &m_isGameClear);
		break;
	case CLIENT_GAME_SCENE:
		delete m_pScene;
		m_pScene = new ClientGameScene(m_pLibrary, m_hWnd, m_pIPadd, &m_isGameClear);
		break;
	case RESULT_SCENE:
		delete m_pScene;
		m_pScene = new ResultScene(m_pLibrary, m_isGameClear);
		break;
	case STAFF_SCENE:
		delete m_pScene;
		m_pScene = new StaffScene(m_pLibrary);
		break;
	case END_SCENE:
		return true;
		break;
	default:
		MessageBox(0, "m_NextSceneに予期していない数値が入っています。", "", MB_OK);
		break;
	}

	m_NextScene = m_pScene->Control();
	
	return false;
}

void SceneManager::Draw()
{
	m_pLibrary->DrawReady();

	m_pScene->Draw();

	m_pLibrary->DrawEnd();

}