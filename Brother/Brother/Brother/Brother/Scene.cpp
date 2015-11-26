#include "Scene.h"

unsigned int Scene::m_time;

Scene::Scene(Library* pLibrary) :m_pLibrary(pLibrary), m_NextScene(SCENE_NONE)
{
	for (int i = 0; i < ANALOG_MAX; i++)
	{
		m_PadState[i] = false;
		m_PadOldState[i] = false;
	}
}

Scene::~Scene()
{

}


