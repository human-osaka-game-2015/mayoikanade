#ifndef CONNECTINGSCENE_H
#define CONNECTINGSCENE_H

#include "Scene.h"
class Library;

class ConnectingScene:public Scene
{
private:

public:
	ConnectingScene(Library* pLibrary);
	~ConnectingScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif