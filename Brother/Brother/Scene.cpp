#include "Scene.h"


//Sceneのタイムを格納する
//すべてのSceneで共有するためにStaticにしている
unsigned int Scene::m_time;


/**
 * Sceneクラスのコンストラクタ
 * @param[in] pLibrary	ライブラリクラス
 */
Scene::Scene(Library* pLibrary) :
m_pLibrary(pLibrary), 
m_NextScene(SCENE_NONE)
{
	for (int i = FOR_DEFAULT_INIT; i < ANALOG_MAX; i++)
	{
		m_PadState[i] = false;
		m_PadOldState[i] = false;
	}
}

/**
 * SceneManagerクラスのデストラクタ
 */
Scene::~Scene()
{

}


