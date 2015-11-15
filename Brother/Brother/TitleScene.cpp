#include "TitleScene.h"


TitleScene::TitleScene(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{

}

TitleScene::~TitleScene()
{

}

SCENE_NUM TitleScene::Control()
{
	return m_NextScene;
}

void TitleScene::Draw()
{

}

void TitleScene::PadCheck()
{

}
