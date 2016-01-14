#include "SceneChangeListener.h"

SceneChangeListener::SceneChangeListener(SCENE_NUM* SceneNum, bool* isClear)
{
	m_pNextScene = SceneNum;
	m_pisGameClear = isClear;
}

SceneChangeListener::~SceneChangeListener()
{

}

void SceneChangeListener::Update(GAMEUPDATE_NUM UpdateId)
{
	if (UpdateId == GAMEOVER_UPDATE)
	{
		*m_pisGameClear = false;
		*m_pNextScene = RESULT_SCENE;
	}
}
