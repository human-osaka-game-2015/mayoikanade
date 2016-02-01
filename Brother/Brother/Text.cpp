#include "Text.h"
#include "ModeManager.h"
#include "Library.h"
#include "ServerGameScene.h"


/**
 * Text�N���X�̃R���X�g���N�^
 * @param[in] pLibrary ���C�u�����N���X
 * @param[in] pPadState �X�e�B�b�N�̏�񂪊i�[�����z��
 * @param[in] pPadOldSta ��O�̃X�e�B�b�N�̏�񂪊i�[�����z��te
 * @param[in] pButtonState �{�^���̏�񂪊i�[�����z��
 */
Text::Text(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState) :
m_pLibrary(pLibrary), 
m_darkness_alpha(COLORMIN), 
m_brother_alpha(COLORMIN), 
m_textbox_alpha(COLORMIN), 
m_message_count(), 
m_message_old(0), 
m_send_count(0), 
m_message_UV(0), 
m_message_right(0.0f), 
m_text_is_unsolved(true), 
m_all_alpha_is_max(false), 
m_text_is_end(false), 
m_message_wait(false),
m_pPadState(pPadState),
m_pPadOldState(pPadOldState),
m_pButtonState(pButtonState)
{
}

/**
 * Text�N���X�̃f�X�g���N�^
 */
Text::~Text()
{

}

/**
 * Text�N���X�̃R���g���[���֐�
 */
void Text::Control()
{
	this->m_CurrentMode = this->m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL://�ʏ펞

		break;
	case TEXT://�Z���t�̊Ԃ���
		TextControl();
		break;
	case GAMEOVEREFFECT://�ꉞ

		break;
	case GAMEOVER://�ꉞ

		break;
	}
}

/**
 * Text�̕`��֐�
 */
void Text::Draw()
{
	m_CurrentMode = m_pModeManager->GetMode();

	switch (m_CurrentMode)
	{
	case NORMAL://�ʏ펞

		break;
	case TEXT://�Z���t�̊Ԃ���
		TextDraw();
		break;
	case GAMEOVEREFFECT://�ꉞ

		break;
	case GAMEOVER://�ꉞ

		break;

	}
}

/**
 * ModeManager���Z�b�g����֐�
 * @param[in] pModeManager �Z�b�g����ModeManager�̃|�C���^
 */
void Text::ModeManagerSet(ModeManager* pModeManager)
{
	this->m_pModeManager = pModeManager;
}

/**
 * Text�̃R���g���[���֐�
 */
void Text::TextControl()
{
	m_Pos[DARKNESS].x = 640.0f;		//--------------------------------------------
	m_Pos[DARKNESS].y = 512.0f;		//
	m_Pos[DARKNESS].h = 1200.0f;	//
	m_Pos[DARKNESS].w = 1400.0f;	//�@���̕�Elegant����Ȃ��ȁE�E�E
	//
	m_Pos[BROTHER_A].x = 346.0f;	//
	m_Pos[BROTHER_A].y = 284.0f;	//
	m_Pos[BROTHER_A].w = 512.0f;	//
	m_Pos[BROTHER_A].h = 320.0f;	//
	//
	m_Pos[BROTHER_O].x = 934.0f;	//
	m_Pos[BROTHER_O].y = 284.0f;	//
	m_Pos[BROTHER_O].w = 512.0f;	//
	m_Pos[BROTHER_O].h = 320.0f;	//
	//
	m_Pos[NAMEBOX_A].x = 202.5f;	//
	m_Pos[NAMEBOX_A].y = 406.5f;	//
	m_Pos[NAMEBOX_A].w = 225.0f;	//
	m_Pos[NAMEBOX_A].h = 75.0f;		//
	//
	m_Pos[NAMEBOX_O].x = 1077.5f;	//
	m_Pos[NAMEBOX_O].y = 406.5f;	//
	m_Pos[NAMEBOX_O].w = 225.0f;	//
	m_Pos[NAMEBOX_O].h = 75.0f;		//
	//
	m_Pos[TEXTBOX].x = 640.0f;		//
	m_Pos[TEXTBOX].y = 634.0f;		//
	m_Pos[TEXTBOX].w = 1100.0f;		//
	m_Pos[TEXTBOX].h = 380.0f;		//
	//
	m_Pos[MESSAGE_A].x = 640.0f;	//
	m_Pos[MESSAGE_A].y = 634.0f;	//
	m_Pos[MESSAGE_A].w = 1100.0f;	//
	m_Pos[MESSAGE_A].h = 300.0f;	//
	//
	m_Pos[MESSAGE_O].x = 640.0f;	//
	m_Pos[MESSAGE_O].y = 634.0f;	//
	m_Pos[MESSAGE_O].w = 1100.0f;	//
	m_Pos[MESSAGE_O].h = 300.0f;	//---------------------------------------
	if (m_textbox_alpha == COLORMAX)
	{
		m_all_alpha_is_max = true;
	}
	if (m_darkness_alpha <= COLORMAX - LIGHT_INTENSITY&&!m_all_alpha_is_max)
	{
		m_darkness_alpha++;
	}
	if (m_brother_alpha < COLORMAX && !m_all_alpha_is_max&&m_darkness_alpha >= COLORMAX - LIGHT_INTENSITY)
	{
		m_brother_alpha++;
	}
	if (m_brother_alpha == COLORMAX && !m_all_alpha_is_max)
	{
		m_textbox_alpha = COLORMAX;
	}

	if (m_all_alpha_is_max)
	{
		m_pLibrary->Check(GAMEPAD1);
		if (m_pButtonState[XINPUT_BUTTON_A] == PAD_PUSH && m_message_wait == false && m_text_is_end == false)
		{
			m_message_count += 1;
			m_message_wait = true;
			if (m_message_count == 3)
			{
				m_text_is_end = true;
			}
		}
	}

	if (m_message_count > 0 && m_message_count<3)
	{
		if (m_message_count != m_message_old)
		{
			m_message_right = 90;
			m_message_UV = 0;
			m_send_count = 0;
			m_message_old = m_message_count;
		}
		if (m_message_right < LAST_LIGHT)
		{
			m_send_count += 1;
			m_message_right = static_cast<float>(m_send_count*TEXT_SEND);
		}
		else
		{
			m_message_wait = false;
		}
	}

	if (m_text_is_end&&m_message_count == 3)
	{

		if (m_brother_alpha > COLORMIN)
		{
			m_brother_alpha--;
			m_textbox_alpha--;
		}
		if (m_brother_alpha <= COLORMIN && m_darkness_alpha>0)
		{
			m_darkness_alpha--;
		}
		if (m_darkness_alpha <= COLORMIN)
		{
			m_text_is_unsolved = false;
		}

	}

}

/**
 * Text�̕`��֐�
 */
void Text::TextDraw()
{
	CustomVertex darkness[SQUARE_VERTEX];
	CustomVertex brother_a[SQUARE_VERTEX];
	CustomVertex brother_o[SQUARE_VERTEX];
	CustomVertex namebox_a[SQUARE_VERTEX];
	CustomVertex namebox_o[SQUARE_VERTEX];
	CustomVertex textbox[SQUARE_VERTEX];
	CustomVertex message_a[SQUARE_VERTEX];
	CustomVertex message_o[SQUARE_VERTEX];

	m_pLibrary->MakeVertex(YOUNGERBROTHER_LIFEBAR, darkness);
	m_pLibrary->MakeVertex(STAND_BROTHER, brother_a);
	m_pLibrary->MakeVertex(STAND_YOUNGERBROTHER, brother_o);
	m_pLibrary->MakeVertex(GRASS_01, namebox_a);
	m_pLibrary->MakeVertex(GRASS_01, namebox_o);
	m_pLibrary->MakeVertex(SPEAK_BROTHER, textbox);
	m_pLibrary->MakeVertex(SPEAK_YOUNGERBROTHER, message_a);
	m_pLibrary->MakeVertex(SPEAK_YOUNGERBROTHER, message_o);

	m_pLibrary->xySet(m_Pos[DARKNESS], darkness);
	m_pLibrary->xySet(m_Pos[BROTHER_A], brother_a);
	m_pLibrary->xySet(m_Pos[BROTHER_O], brother_o);
	m_pLibrary->xySet(m_Pos[NAMEBOX_O], namebox_a);
	m_pLibrary->xySet(m_Pos[NAMEBOX_A], namebox_o);
	m_pLibrary->xySet(m_Pos[TEXTBOX], textbox);
	m_pLibrary->xySet(m_Pos[MESSAGE_A], message_a);
	m_pLibrary->xySet(m_Pos[MESSAGE_O], message_o);


	for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
	{
		darkness[i].color = D3DCOLOR_ARGB(m_darkness_alpha, COLORMAX, COLORMAX, COLORMAX);
		brother_a[i].color = D3DCOLOR_ARGB(m_brother_alpha, COLORMAX, COLORMAX, COLORMAX);
		brother_o[i].color = D3DCOLOR_ARGB(m_brother_alpha, COLORMAX, COLORMAX, COLORMAX);
		namebox_a[i].color = D3DCOLOR_ARGB(m_textbox_alpha, COLORMAX, COLORMAX, COLORMAX);
		namebox_o[i].color = D3DCOLOR_ARGB(m_textbox_alpha, COLORMAX, COLORMAX, COLORMAX);
		textbox[i].color = D3DCOLOR_ARGB(m_textbox_alpha, COLORMAX, COLORMAX, COLORMAX);
		message_a[i].color = D3DCOLOR_ARGB(COLORMAX, COLORMAX, COLORMAX, COLORMAX);
		message_o[i].color = D3DCOLOR_ARGB(COLORMAX, COLORMAX, COLORMAX, COLORMAX);
	}

	m_pLibrary->DrawTexture(TEX_GAME, darkness);
	m_pLibrary->DrawTexture(TEX_GAME, brother_a);
	m_pLibrary->DrawTexture(TEX_GAME, brother_o);
	m_pLibrary->DrawTexture(TEX_GAME, namebox_a);
	m_pLibrary->DrawTexture(TEX_GAME, namebox_o);
	m_pLibrary->DrawTexture(TEX_GAME, textbox);

	switch (m_message_count)
	{
	case 1:
		message_o[1].tu = message_o[2].tu = message_o[0].tu + ((message_o[1].tu - message_o[0].tu)*m_send_count / 60 / TEXT_SPEED);
		message_o[1].x = message_o[2].x = message_o[0].x + m_message_right;
		m_pLibrary->DrawTexture(TEX_GAME, message_o);
		break;

	case 2:
		message_a[1].tu = message_a[2].tu = message_a[0].tu + ((message_a[1].tu - message_a[0].tu)*m_send_count / 60 / TEXT_SPEED);
		message_a[1].x = message_a[2].x = message_a[0].x + m_message_right;
		m_pLibrary->DrawTexture(TEX_GAME, message_a);
		break;

	case 3:
		for (int i = FOR_DEFAULT_INIT; i < SQUARE_VERTEX; i++)
		{
			message_a[i].color = D3DCOLOR_ARGB(m_textbox_alpha, COLORMAX, COLORMAX, COLORMAX);
		}
		m_pLibrary->DrawTexture(TEX_GAME, message_a);
	default:

		break;
	}

}

/**
 * Message���I��������`�F�b�N����֐�
 * @return text���I�������
 */
bool Text::GetMessageEnd()
{
	return m_text_is_unsolved;
}


