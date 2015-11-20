#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <d3dx9.h>
class Library;
class Scene;
enum SCENE_NUM;



class SceneManager
{
private:
	SCENE_NUM	m_NextScene;
	Library*	m_pLibrary;

public:
	SceneManager(Library* pLibrary);
	~SceneManager();
	bool Control();
	void Draw();
	Scene*		m_pScene;	
};

#endif