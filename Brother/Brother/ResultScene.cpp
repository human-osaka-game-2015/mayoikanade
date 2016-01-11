#include "ResultScene.h"
#include "ResultBackGround.h"
#include "ResultClock.h"



ResultScene::ResultScene(Library* pLibrary) :
Scene(pLibrary)
{
	m_pResultBackGround = new ResultBackGround();
	m_pResultClock = new ResultClock();
	
	m_NextScene = SCENE_NONE;

}

ResultScene::~ResultScene()
{
	delete m_pResultClock;
	delete m_pResultBackGround;
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
