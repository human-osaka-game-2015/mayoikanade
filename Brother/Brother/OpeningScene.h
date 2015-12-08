#ifndef OPENINGSCENE_H
#define OPENINGSCENE_H

#include "Scene.h"
class Library;

class OpeningScene:public Scene
{
private:



public:
	OpeningScene(Library* pLibrary);
	~OpeningScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif