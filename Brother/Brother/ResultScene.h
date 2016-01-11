#ifndef RESULTSCENE_H
#define RESULTSCENE_H

#include "Scene.h"
class Library;
class ResultBackGround;
class ResultClock;

class ResultScene:public Scene
{
private:
	ResultBackGround*	m_pResultBackGround;
	ResultClock*		m_pResultClock;

public:
	ResultScene(Library* pLibrary);
	~ResultScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif