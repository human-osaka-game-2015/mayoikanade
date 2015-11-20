#include "OpeningScene.h"


OpeningScene::OpeningScene(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{

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
