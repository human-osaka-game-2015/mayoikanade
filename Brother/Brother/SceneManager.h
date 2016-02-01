#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#define IP_NUM 16

#include <d3dx9.h>

class Library;
class Scene;
enum SCENE_NUM;

class SceneManager
{
private:
	SCENE_NUM	m_NextScene;
	Library*	m_pLibrary;
	HWND		m_hWnd;

public:
	SceneManager(Library* pLibrary, HWND hWnd);
	~SceneManager();
	bool Control();
	void Draw(); 
	
	Scene*		m_pScene;
	char m_pIPadd[IP_NUM];
	bool m_isGameClear;
};

#endif