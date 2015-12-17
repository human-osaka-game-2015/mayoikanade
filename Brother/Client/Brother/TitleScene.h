#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "Scene.h"

class Library;
class TitleBackGround;
class TitleTimeManager;
class TitleSelectManager;
class TitleName;

enum TITLE_VERTEXINFO_ID
{
	TITLE_BACKGROUND,
	TITLE_NAME,
	TITLE_CURSOL01,
	TITLE_CURSOL02,
	TITLE_CURSOL03,
	TITLE_CURSOL04,
	TITLE_START,
	TITLE_STAFF,
	TITLE_END,
	TITLE_BLACK,
	TITLE_VERTEXINFO_MAX
};

enum TITLEANIMA_ID
{
	CURSOL_ANIMA,
	TITLEANIMA_ID_MAX
};

enum TITLESOUND_ID
{
	TITLE_BGM,
	TITLESOUND_ID_MAX
};

class TitleScene:public Scene
{
private:
	//TitleScene内オブジェクト
	TitleBackGround*	m_pTitleBackGround;
	TitleSelectManager*	m_pTitleSelectManager;
	TitleTimeManager*	m_pTitleTimeManager;
	TitleName*			m_pTitleName;

	bool isTimeOver = false;
	

public:
	TitleScene(Library* pLibrary);
	~TitleScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif