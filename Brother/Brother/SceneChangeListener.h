#ifndef SCENECHANGELISTENER_H
#define SCENECHANGELISTENER_H

#include "Scene.h"

enum GAMEUPDATE_NUM
{
	GAMEOVER_UPDATE,
	GAMECLEAR_UPDATE,
	GAMEUPDATE_NUM_MAX
};

class SceneChangeListener
{
private:
	SCENE_NUM*	m_pNextScene;
	bool*		m_pisGameClear;

public:
	SceneChangeListener(SCENE_NUM* SceneNum,bool* isClear);
	~SceneChangeListener();
	void Update(GAMEUPDATE_NUM UpdateId);

};



#endif