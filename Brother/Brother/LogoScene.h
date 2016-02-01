#ifndef LOGOSCENE_H
#define LOGOSCENE_H



#include"Scene.h"

class Library;
class LogoBackGround;

enum LOGO_VERTEXINFO_ID
{
	TEAMLOGO,
	LOGO_VERTEXINFO_MAX
};

class LogoScene:public Scene
{
private:
	LogoBackGround*	m_pLogoBackGround;

public:
	LogoScene(Library* pLibrary);
	~LogoScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};


#endif