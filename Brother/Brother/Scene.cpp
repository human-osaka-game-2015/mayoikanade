#include "Scene.h"


//Scene�̃^�C�����i�[����
//���ׂĂ�Scene�ŋ��L���邽�߂�Static�ɂ��Ă���
unsigned int Scene::m_time;


/**
 * Scene�N���X�̃R���X�g���N�^
 * @param[in] pLibrary	���C�u�����N���X
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
 * SceneManager�N���X�̃f�X�g���N�^
 */
Scene::~Scene()
{

}


