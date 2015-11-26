#include "SceneChangeListener.h"

SceneChangeListener::SceneChangeListener(SCENE_NUM* SceneNum)
{
	m_pNextScene = SceneNum;
}

SceneChangeListener::~SceneChangeListener()
{

}

void SceneChangeListener::Update(GAMEUPDATE_NUM UpdateId)
{
	if (UpdateId == GAMEOVER_UPDATE)
	{
		*m_pNextScene = RESULT_SCENE;
	}
}
