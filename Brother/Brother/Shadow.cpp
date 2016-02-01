#include "Shadow.h"
#include "ServerGameScene.h"
#include "Library.h"
#include "GameTimeManager.h"
#include "ModeManager.h"


/**
 * Shadow�N���X�̃R���X�g���N�^
 * @param[in] pLibrary ���C�u�����N���X�̃|�C���^
 * @param[in] pGameTimeManager GameTimeManager�N���X�̃|�C���^
 */
Shadow::Shadow(Library* pLibrary, GameTimeManager* pGameTimeManager) :
m_pLibrary(pLibrary), m_GameTimeManager(pGameTimeManager)
{
	m_Pos.x = SHADOW_POS_X;
	m_Pos.y = SHADOW_POS_Y;
	m_Pos.h = SHADOW_POS_H;
	m_Pos.w = SHADOW_POS_W;

}

/**
 * Shadow�N���X�̃f�X�g���N�^
 */
Shadow::~Shadow()
{

}

/**
 * Shadow�̃R���g���[���֐�
 */
void Shadow::Control()
{
	switch (m_pModeManager->GetMode())
	{
	case NORMAL:

		if (m_GameTimeManager->GetGameTime() % ONE_SECCOND == ONE_FRAME)
		{
			m_Pos.h -= SHADOW_REDUCTION;
			m_Pos.w -= SHADOW_REDUCTION;
		}

		if (m_Pos.h <= SHADOW_MIN || m_Pos.w <= SHADOW_MIN)
		{
			m_Pos.h = SHADOW_MIN;
			m_Pos.w = SHADOW_MIN;
		}

		break;
	case TEXT:

		break;
	case GAMEOVEREFFECT:

		m_Pos.h -= SHADOW_REDUCTION;
		m_Pos.w -= SHADOW_REDUCTION;

		if (m_Pos.h <= SHADOW_MIN || m_Pos.w <= SHADOW_MIN)
		{
			m_Pos.h = SHADOW_MIN;
			m_Pos.w = SHADOW_MIN;
		}

		break;
	case GAMEOVER:

		break;
	}
}

/**
 * �e�̕`��֐�
 */
void Shadow::Draw()
{
	CustomVertex StencilVertex[SQUARE_VERTEX] =
	{
		{ STENCIL_X, STENCIL_Y, STENCIL_Z, STENCIL_RHW, STENCIL_COLOR, STENCIL_TU_MIN, STENCIL_TV_MIN },
		{ STENCIL_X, STENCIL_Y, STENCIL_Z, STENCIL_RHW, STENCIL_COLOR, STENCIL_TU_MAX, STENCIL_TV_MIN },
		{ STENCIL_X, STENCIL_Y, STENCIL_Z, STENCIL_RHW, STENCIL_COLOR, STENCIL_TU_MAX, STENCIL_TV_MAX },
		{ STENCIL_X, STENCIL_Y, STENCIL_Z, STENCIL_RHW, STENCIL_COLOR, STENCIL_TU_MIN, STENCIL_TV_MAX }
	};

	m_pLibrary->xySet(m_Pos, StencilVertex);

	m_pLibrary->AlphaTestReady(DEFAULT_REF);

	m_pLibrary->StencilRefSet(SHADOW_REF);
	m_pLibrary->StencilDrawReady();

	

	m_pLibrary->DrawTexture(STENCIL, StencilVertex);

	m_pLibrary->StencilRefSet(SHADOW_REF);
	m_pLibrary->StencilDrawEnd();

	m_pLibrary->AlphaTestEnd();
}

/**
 * ModeManager�N���X�̃Z�b�g�֐�
 * @param[in] ModeManager�N���X�ւ̃|�C���^
 */
void Shadow::ModeManagerSet(ModeManager* pModeManager)
{
	m_pModeManager = pModeManager;
}

/**
 * �e������؂��ĉ�ʂ��^���ÂɂȂ��������`�F�b�N����
 * @return �^���ÂɂȂ�����true���Ԃ�
 */
bool Shadow::ShadowCheck()
{
	if (m_Pos.w <= SHADOW_MIN)
	{
		return true;
	}

	return false;
}

