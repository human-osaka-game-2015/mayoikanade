#ifndef RESULTSCENE_H
#define RESULTSCENE_H

#include "Scene.h"
class Library;
class ResultBackGround;
class ResultClock;
class ResultText;


enum GAMECLEAR_VERTEXINFO_ID
{
	GAMECLEAR_BACKGROUND,
	GAMECLEAR_CLOCK01,		//è„
	GAMECLEAR_CLOCK02,		//íÜ
	GAMECLEAR_CLOCK03,		//â∫
	GAMECLEAR_CLOCK_LONG_HAND,
	GAMECLEAR_CLOCK_SHORT_HAND,
	GAMECLEAR_CLEAR_TEXT,
	GAMECLEAR_TITLE_TEXT,

	GAMECLEAR_VERTEXINFO_MAX
};


enum GAMEOVER_VERTEXINFO_ID
{
	GAMEOVER_BACKGROUND,
	GAMEOVER_GAMEOVER_TEXT,
	GAMEOVER_TITLE_TEXT,
	GAMEOVER_CLOCK_SHORT_HAND,
	GAMEOVER_CLOCK_LONG_HAND,

	GAMEOVER_VERTEXINFO_MAX
};


class ResultScene:public Scene
{
private:
	ResultBackGround*	m_pResultBackGround;
	ResultClock*		m_pResultClock;
	ResultText*			m_pResultText;
	bool				m_isGameClear;

public:
	ResultScene(Library* pLibrary, bool isGameClear);
	~ResultScene();
	virtual SCENE_NUM Control();
	virtual void Draw();
	virtual void PadCheck();

};

#endif