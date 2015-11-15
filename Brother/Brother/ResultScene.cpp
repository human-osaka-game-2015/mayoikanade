#include "ResultScene.h"


ResultScene::ResultScene(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{

}

ResultScene::~ResultScene()
{

}

SCENE_NUM ResultScene::Control()
{
	return m_NextScene;
}

void ResultScene::Draw()
{

}

void ResultScene::PadCheck()
{

}
