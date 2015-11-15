#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_
#include <Windows.h>


class Library;
class SceneManager;

class GameMain
{
private:

public:
	GameMain(HWND hWnd);
	~GameMain();
	SceneManager*	m_pSceneManager;
	Library*		m_pLibrary;

};

#endif