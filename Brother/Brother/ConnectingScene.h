#ifndef _CONNECTINGSCENE_H_
#define _CONNECTINGSCENE_H_
#include "Scene.h"
class Library;

class ConnectingScene:public Scene
{
private:
	SCENE_NUM				m_NextScene;
	Library*				m_pLibrary;

public:
	ConnectingScene(Library* pLibrary);
	~ConnectingScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif