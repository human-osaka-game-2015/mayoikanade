#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_
#include "Scene.h"
class Library;

class TitleScene:public Scene
{
private:
	SCENE_NUM				m_NextScene;
	Library*				m_pLibrary;

public:
	TitleScene(Library* pLibrary);
	~TitleScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif