#include "ResultBackGround.h"
#include "ResultScene.h"
#include "Library.h"


/**
 * ResultBackGround�N���X�̃R���X�g���N�^
 * @param [in] pLibrary ���C�u�����N���X
 * @param [in] isGameClear �Q�[���N���A�������̃t���O
 */
ResultBackGround::ResultBackGround(Library* pLibrary, bool isGameClear) :
m_pLibrary(pLibrary),
m_isGameClear(isGameClear),
m_alpha(COLORMIN),
m_FadeTime(RESULTBACKGROUND_INIT_FADE_TIME)
{
	//�N���A�������ɂ���ď�����������W��ύX���Ă���
	if (m_isGameClear == true)
	{
		m_pLibrary->MakePosition(GAMECLEAR_BACKGROUND, &m_BackGroundPos);
	}
	else
	{
		m_pLibrary->MakePosition(GAMEOVER_BACKGROUND, &m_BackGroundPos);
	}
	
	m_BackGroundPos.x = RESULTBACKGROUND_POS_X;
	m_BackGroundPos.y = RESULTBACKGROUND_POS_Y;
}

/**
 * ResultBackGround�N���X�̃f�X�g���N�^
 */
ResultBackGround::~ResultBackGround()
{

}

/**
 * ResultBackGround�̃R���g���[���֐�
 */
void ResultBackGround::Control()
{
	if (m_FadeTime >= RESULTBACKGROUND_FADE_TIME)
	{
		if (m_alpha < COLORMAX)
		{
			m_alpha++;
		}
		else if (m_alpha > COLORMAX)
		{
			m_alpha = COLORMAX;
		}
	}
	else
	{
		m_FadeTime++;
	}

}

/**
 * ResultBackGround�̕`��֐�
 */
void ResultBackGround::Draw()
{
	if (m_isGameClear == true)
	{
		ClearDraw();
	}
	else
	{
		OverDraw();
	}
	
}


/**
 * GameClear���̕`��֐�
 */
void ResultBackGround::ClearDraw()
{
	CustomVertex BackGroundVertex[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(GAMECLEAR_BACKGROUND, BackGroundVertex);

	m_pLibrary->xySet(m_BackGroundPos, BackGroundVertex);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		BackGroundVertex[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_GAMECLEAR, BackGroundVertex);
}

/**
 * GameOver���̕`��֐�
 */
void ResultBackGround::OverDraw()
{
	CustomVertex BackGroundVertex[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(GAMEOVER_BACKGROUND, BackGroundVertex);

	m_pLibrary->xySet(m_BackGroundPos, BackGroundVertex);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		BackGroundVertex[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_GAMEOVER, BackGroundVertex);
}
