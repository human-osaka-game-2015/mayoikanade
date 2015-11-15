#include "Scene.h"

Scene::Scene()
{
	for (int i = 0; i < PAD_MAX; i++)
	{
		m_PadState[i] = false;
		m_PadOldState[i] = false;
	}
	
}

Scene::~Scene()
{

}


