#include "ResultScene.h"



ResultScene::ResultScene(Library* pLibrary) :Scene(pLibrary)
{
	//time‚Ì‰Šú‰»
	m_time = 0;

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
