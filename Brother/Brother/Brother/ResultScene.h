#ifndef RESULTSCENE_H
#define RESULTSCENE_H

#include "Scene.h"
class Library;

class ResultScene:public Scene
{
private:


public:
	ResultScene(Library* pLibrary);
	~ResultScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif