#include "TitleTimeManager.h"
#include "TitleScene.h"


/**
 * TitleTimeManager�N���X�̃R���X�g���N�^
 * @param[in]  pLibrary	���C�u�����N���X
 * @param[out] GameTime	Scene��time��n��
 */
TitleTimeManager::TitleTimeManager(Library* pLibrary, unsigned int& GameTime) :
m_pLibrary(pLibrary), 
m_GameTime(GameTime),
m_alpha(COLORMAX)
{
	m_GameTime = TIME_INIT;

	//�����ʒu�ɐݒ�
	m_Pos.x = TITLEBLACKOUT_X;
	m_Pos.y = TITLEBLACKOUT_Y;

	//�傫�����ݒ�
	m_Pos.w = TITLEBLACKOUT_W;
	m_Pos.h = TITLEBLACKOUT_H;
}

/**
 * TitleScene�N���X�̃f�X�g���N�^
 */
TitleTimeManager::~TitleTimeManager()
{

}

/**
 * TitleTimeManager�N���X�̃R���X�g���N�^
 * @param[in] pLibrary	���C�u�����N���X
 * @param[in] hWnd		�E�B���h�E�n���h��
 * @return �t�F�[�h�A�E�g������true��Ԃ�
 */
bool TitleTimeManager::Control()
{
	//�^�C���̃J�E���g
	m_GameTime++;
	

	if (m_GameTime > FADEOUT_TIME)
	{
		m_alpha++;
		if (m_alpha == COLORMAX)
		{
			return true;
		}
	}
	else if (m_alpha != COLORMIN)
	{
		m_alpha--;
	}

	return false;
}

/**
 * TitleTimeManager�̕`��֐�
 */
void TitleTimeManager::Draw()
{
	CustomVertex blackout[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(TITLE_BLACK, blackout);
	m_pLibrary->xySet(m_Pos, blackout);

	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		blackout[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_TITLE, blackout);
}

