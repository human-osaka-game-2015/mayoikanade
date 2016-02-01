#include "LogoBackGround.h"
#include "LogoScene.h"



/**
 * LogoBackGround�N���X�̃R���X�g���N�^
 * @param[in] pLibrary ���C�u�����N���X
 */
LogoBackGround::LogoBackGround(Library* pLibrary) :
m_pLibrary(pLibrary),
m_alpha(COLORMIN),
m_isFadeIn(true)
{
	//�����ɗ���悤�ɏ����l�ݒ�
	m_Pos.x = LOGOBACKGROUNDPOS_X;
	m_Pos.y = LOGOBACKGROUNDPOS_Y;
}

/**
 * LogoBackGround�N���X�̃f�X�g���N�^
 */
LogoBackGround::~LogoBackGround()
{

}

/**
 * LogoBackGround�̃R���g���[��
 * @return �t�F�[�h�A�E�g���I��������̃t���O
 */
bool LogoBackGround::Control()
{
	if (m_isFadeIn == true)
	{
		m_alpha++;
		if (m_alpha == COLORMAX)
		{
			m_isFadeIn = false;
		}
	}
	else
	{
		m_alpha--;
		if (m_alpha == COLORMIN)
		{
			return true;
		}
	}

	return false;
}

/**
 * LogoBackGround�̕`��֐�
 */
void LogoBackGround::Draw()
{
	CustomVertex background[SQUARE_VERTEX];

	m_pLibrary->MakePosition(TEAMLOGO,&m_Pos);
	
	m_pLibrary->MakeVertex(TEAMLOGO, background);
	m_pLibrary->xySet(m_Pos, background);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		background[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_LOGO, background);
}