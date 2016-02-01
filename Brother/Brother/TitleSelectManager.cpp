#include "TitleSelectManager.h"
#include "TitleScene.h"


/**
 * TitleSelectManager�N���X�̃R���X�g���N�^
 * @param [in] pLibrary ���C�u�����N���X
 * @param [in] pPadState GamePad�̃X�e�B�b�N�̏�Ԃ��i�[�����
 * @param [in] pPadOldState GamePad�̃X�e�B�b�N�̑O�̏�Ԃ��i�[�����
 * @param [in] pButtonState GamePad�̃{�^���̏�Ԃ��i�[�����
 */
TitleSelectManager::TitleSelectManager(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState):
m_pLibrary(pLibrary), 
m_PadState(pPadState), 
m_PadOldState(pPadOldState), 
m_pButtonState(pButtonState),
m_CurrentSelect(GAME_START),
m_alpha(COLORMAX)
{
	m_StartPos.x = STARTPOS_X;
	m_StartPos.y = STARTPOS_Y;
	m_StaffPos.x = STAFFPOS_X;
	m_StaffPos.y = STAFFPOS_Y;
	m_EndPos.x = ENDPOS_X;
	m_EndPos.y = ENDPOS_Y;
	m_CursolPos.w = CURSOL_WIDTH;
	m_CursolPos.h = CURSOL_HEIGHT;

	m_pLibrary->InitAnima(CURSOL_ANIMA);
}


/**
 * TitleSelectManager�N���X�̃f�X�g���N�^
 */
TitleSelectManager::~TitleSelectManager()
{

}


/**
 * TitleSelect�̃R���g���[���֐�
 * @return �I�����ꂽ����
 */
TITLESELECT_ID TitleSelectManager::Control()
{

	//�R���g���[���[�̓��͂ŏ�Ԃ�ύX����
	//�J�[�\���ʒu���ς��悤�ɂ��Ă���
	if (m_PadState[ANALOG_UP] == true && m_PadOldState[ANALOG_UP] == false)
	{
		switch (m_CurrentSelect)
		{
		case GAME_START:
			m_CurrentSelect = GAME_STAFF;
			break;
		case GAME_STAFF:
			m_CurrentSelect = GAME_START;
			break;
		default:

			break;
		}
	}
	else if (m_PadState[ANALOG_DOWN] == true && m_PadOldState[ANALOG_DOWN] == false)
	{
		switch (m_CurrentSelect)
		{
		case GAME_START:
			m_CurrentSelect = GAME_STAFF;
			break;
		case GAME_STAFF:
			m_CurrentSelect = GAME_START;
			break;
		default:

			break;
		}
	}
	else if (m_PadState[ANALOG_LEFT] == true && m_PadOldState[ANALOG_LEFT] == false)
	{
		switch (m_CurrentSelect)
		{
		case GAME_START:
			m_CurrentSelect = GAME_END;
			break;
		case GAME_STAFF:
			m_CurrentSelect = GAME_END;
			break;
		default:

			break;
		}
	}
	else if (m_PadState[ANALOG_RIGHT] == true && m_PadOldState[ANALOG_RIGHT] == false)
	{
		switch (m_CurrentSelect)
		{
		case GAME_END:
			m_CurrentSelect = GAME_START;
			break;
		default:

			break;
		}
	}


	//A�{�^���������ꂽ�猻�ݎw���Ă���I�����ڂ�Ԃ�
	if (m_pButtonState[XINPUT_BUTTON_A] == PAD_PUSH)
	{
		return m_CurrentSelect;
	}

	//�ʏ��TitleSelectNone��Ԃ�
	return TITLESELECT_NONE;
}


/**
 * TitleSelect�̕`��֐�
 */
void TitleSelectManager::Draw()
{
	CustomVertex Start[SQUARE_VERTEX];
	CustomVertex Staff[SQUARE_VERTEX];
	CustomVertex End[SQUARE_VERTEX];
	CustomVertex Cursol[SQUARE_VERTEX];

	//�J�[�\���̈ʒu�ݒ�
	switch (m_CurrentSelect)
	{
	case GAME_START:
		m_CursolPos.x = START_CURSOL_POSX;
		m_CursolPos.y = START_CURSOL_POSY;
		break;
	case GAME_STAFF:
		m_CursolPos.x = STAFF_CURSOL_POSX;
		m_CursolPos.y = STAFF_CURSOL_POSY;
		break;
	case GAME_END:
		m_CursolPos.x = END_CURSOL_POSX;
		m_CursolPos.y = END_CURSOL_POSY;
		break;
	}

	//�J�[�\���̃A�j���[�V����
	int CursolId;
	CursolId = m_pLibrary->AnimaControl(m_CursolCurrentAnima);


	//position�̕������ݒ�
	m_pLibrary->MakePosition(TITLE_START, &m_StartPos);
	m_pLibrary->MakePosition(TITLE_STAFF, &m_StaffPos);
	m_pLibrary->MakePosition(TITLE_END, &m_EndPos);


	//tu�@tv�̐ݒ�
	m_pLibrary->MakeVertex(TITLE_START, Start);
	m_pLibrary->MakeVertex(TITLE_STAFF, Staff);
	m_pLibrary->MakeVertex(TITLE_END, End);
	m_pLibrary->MakeVertex(CursolId, Cursol);


	//X y�̐ݒ�
	m_pLibrary->xySet(m_StartPos, Start);
	m_pLibrary->xySet(m_StaffPos, Staff);
	m_pLibrary->xySet(m_EndPos, End);
	m_pLibrary->xySet(m_CursolPos, Cursol);



	if (m_isSelectFadeout == true)
	{
		m_alpha--;
		if (m_alpha <= SELECT_ALPHA_MIN)
		{
			m_isSelectFadeout = false;
		}
	}
	else
	{
		m_alpha++;
		if (m_alpha >= SELECT_ALPHA_MAX)
		{
			m_isSelectFadeout = true;
		}
	}
	

	switch (m_CurrentSelect)
	{
	case GAME_START:
		for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
		{
			Start[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		}

		break;
	case GAME_STAFF:
		for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
		{
			Staff[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		}

		break;
	case GAME_END:
		for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
		{
			End[i].color = D3DCOLOR_ARGB(m_alpha, COLORMAX, COLORMAX, COLORMAX);
		}


		break;
	}

	//�I�����ڂ̕`��
	m_pLibrary->DrawTexture(TEX_TITLE, Start);
	m_pLibrary->DrawTexture(TEX_TITLE, Staff);
	m_pLibrary->DrawTexture(TEX_TITLE, End);
	m_pLibrary->DrawTexture(TEX_TITLE, Cursol);
}

