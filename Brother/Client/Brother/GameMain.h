#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include <Windows.h>


class Library;
class SceneManager;

class GameMain
{
private:
	HWND m_hWnd;

public:
	GameMain(HWND hWnd);
	~GameMain();
	SceneManager*	m_pSceneManager;
	Library*		m_pLibrary;

};

#endif