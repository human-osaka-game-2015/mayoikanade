#include "ConnectingScene.h"




ConnectingScene::ConnectingScene(Library* pLibrary) :Scene(pLibrary)
{
	//time‚Ì‰Šú‰»
	m_time = 0;
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
