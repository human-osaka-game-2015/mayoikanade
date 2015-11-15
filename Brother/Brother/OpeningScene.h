#ifndef _OPENINGSCENE_H_
#define _OPENINGSCENE_H_
#include "Scene.h"
class Library;

class OpeningScene:public Scene
{
private:
	SCENE_NUM				m_NextScene;
	Library*				m_pLibrary;


public:
	OpeningScene(Library* pLibrary);
	~OpeningScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif