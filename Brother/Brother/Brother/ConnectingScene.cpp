#include "ConnectingScene.h"


ConnectingScene::ConnectingScene(Library* pLibrary) :Scene(pLibrary)
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
