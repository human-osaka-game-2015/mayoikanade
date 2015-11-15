#ifndef _SCENECHANGELISTENER_H_
#define _SCENECHANGELISTENER_H_
#include "Scene.h"

enum GAMEUPDATE_NUM
{
	GAMEOVER_UPDATE,
	GAMEUPDATE_NUM_MAX
};

class SceneChangeListener
{
private:
	SCENE_NUM* m_pNextScene;

public:
	SceneChangeListener(SCENE_NUM* SceneNum);
	~SceneChangeListener();
	void Update(GAMEUPDATE_NUM UpdateId);

};



#endif