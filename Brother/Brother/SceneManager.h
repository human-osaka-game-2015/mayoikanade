#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include <d3dx9.h>
#include "Scene.h"
class Library;



class SceneManager
{
private:
	SCENE_NUM	m_NextScene;
	Library*	m_pLibrary;

public:
	SceneManager(Library* pLibrary);
	~SceneManager();
	void Control();
	void Draw();
	Scene*		m_pScene;
	

	
	
};

#endif