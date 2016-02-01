#ifndef SHADOW_H
#define SHADOW_H

#define SHADOW_POS_X 600		//�e��X���W
#define SHADOW_POS_Y 350		//�e��Y���W
#define SHADOW_POS_W 6000		//�e�̕�
#define SHADOW_POS_H 6000		//�e�̍���

#define SHADOW_REDUCTION 10		//�e�̏k����
#define SHADOW_MIN 0			//�e�̑傫���̍ŏ��l
#define ONE_SECCOND 60			//1�b�̃t���[����
#define ONE_FRAME 0				//��r�p�̐��l
#define STENCIL_X 0.0f			//�X�e���V����Vertex�̏���x���W
#define STENCIL_Y 0.0f			//�X�e���V����Vertex�̏���y���W
#define STENCIL_Z 0.5f			//�X�e���V����Vertex�̏���z���W
#define STENCIL_RHW 1.0f
#define STENCIL_COLOR 0xffffffff
#define STENCIL_TU_MAX 1.0f
#define STENCIL_TV_MAX 1.0f
#define STENCIL_TU_MIN 0.0f
#define STENCIL_TV_MIN 0.0f

#define DEFAULT_REF 0x00		//�f�t�H���g�̃X�e���V���Q�ƒl
#define SHADOW_REF 0x02			//�e�����̎Q�ƒl



#include "Vertex.h"

class Library;
class ModeManager;
class GameTimeManager;
enum GAMEMODE_NUM;


class Shadow
{
private:
	Library*			m_pLibrary;
	ModeManager*		m_pModeManager;
	GameTimeManager*	m_GameTimeManager;
	GAMEMODE_NUM		m_CurrentMode;
	Position			m_Pos;

public:
	Shadow(Library* pLibrary, GameTimeManager* pGameTimeManager);
	~Shadow();
	void Control();
	void Draw();
	void ModeManagerSet(ModeManager* pModeManager);
	bool ShadowCheck();

};



#endif