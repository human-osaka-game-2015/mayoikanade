#include "OpeningScene.h"


OpeningScene::OpeningScene(Library* pLibrary) :Scene(pLibrary)
{
	//time�̏�����
	m_time = 0;

}

OpeningScene::~OpeningScene()
{

}

SCENE_NUM OpeningScene::Control()
{
	return m_NextScene;
}

void OpeningScene::Draw()
{

}

void OpeningScene::PadCheck()
{

}
