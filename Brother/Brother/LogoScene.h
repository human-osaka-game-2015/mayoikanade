#ifndef _LOGOSCENE_H_
#define _LOGOSCENE_H_
#include"Scene.h"
class Library;

class LogoScene:public Scene
{
private:
	SCENE_NUM				m_NextScene;
	Library*				m_pLibrary;


public:
	LogoScene(Library* pLibrary);
	~LogoScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};


#endif