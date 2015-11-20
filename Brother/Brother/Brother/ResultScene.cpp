#include "ResultScene.h"


ResultScene::ResultScene(Library* pLibrary) :Scene(pLibrary)
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
