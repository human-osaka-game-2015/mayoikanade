#include"LogoScene.h"


LogoScene::LogoScene(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{

}

LogoScene::~LogoScene()
{

}

SCENE_NUM LogoScene::Control()
{
	return m_NextScene;
}

void LogoScene::Draw()
{

}

void LogoScene::PadCheck()
{

}
