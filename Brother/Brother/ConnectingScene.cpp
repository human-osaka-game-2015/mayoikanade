#include "ConnectingScene.h"


ConnectingScene::ConnectingScene(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{

}

ConnectingScene::~ConnectingScene()
{

}

SCENE_NUM ConnectingScene::Control()
{
	return m_NextScene;
}

void ConnectingScene::Draw()
{

}

void ConnectingScene::PadCheck()
{

}
