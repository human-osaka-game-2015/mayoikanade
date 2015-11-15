#ifndef _ResultScene_H_
#define _ResultScene_H_
#include "Scene.h"
class Library;

class ResultScene:public Scene
{
private:
	SCENE_NUM				m_NextScene;
	Library*				m_pLibrary;

public:
	ResultScene(Library* pLibrary);
	~ResultScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif