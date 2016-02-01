#include "XInput.h"
#define CONDEADZONE 65535/4 //�R���g���[���[�̃f�b�h�]�[��
#define NO_SIGNAL 0x0000

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "xinput.lib ")


/**
 * XInput�N���X�̃R���X�g���N�^
 */
XInput::XInput()
{
	for (int count = 0; count < GAMEANALOG_MAX; count++)
	{
		for (int i = 0; i < XINPUT_IDMAX; i++)
		{
			m_PadOldState[count][i] = PAD_OFF;
			m_PadState[count][i] = PAD_OFF;
		}
	}
}


/**
 * XInput�N���X�̃f�X�g���N�^
 */
XInput::~XInput()
{

}


/**
 * GamePad�̏�ԃ`�F�b�N�֐�
 * @param[in] pad �`�F�b�N����GamePad
 */
void XInput::Check(XINPUTPAD pad)
{
	XInputGetState(pad, &m_PadControlState[pad].State);
}


/**
 * GamePad�̃{�^���̏�Ԃ��擾����
 * @param[in] id �`�F�b�N����{�^��
 * @param[in] pad �`�F�b�N����GamePad
 */
PADSTATE XInput::GetButtonState(XINPUT_ID id, XINPUTPAD pad)
{
	PADSTATE State;

	switch (id)
	{
	case GAMEPAD_A:
		//���͂���Ă���
		if (m_PadControlState[pad].State.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			//�O�����͂���Ă���
			if (m_PadOldState[pad][id] == PAD_ON)
			{
				State = PAD_ON;
			}
			else
			{
				State = PAD_PUSH;
			}
			m_PadOldState[pad][id] = PAD_ON;
		}
		else 
		{
			//�O�����͂���Ă���
			if (m_PadOldState[pad][id] == PAD_ON)
			{
				State = PAD_RELEASE;
			}
			else
			{
				State = PAD_OFF;
			}
			m_PadOldState[pad][id] = PAD_OFF;
		}
		break;
	case GAMEPAD_B:
		//���͂���Ă���
		if (m_PadControlState[pad].State.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			//�O�����͂���Ă���
			if (m_PadOldState[pad][id] == PAD_ON)
			{
				State = PAD_ON;
			}
			else
			{
				State = PAD_PUSH;
			}
			m_PadOldState[pad][id] = PAD_ON;
		}
		else
		{
			//�O�����͂���Ă���
			if (m_PadOldState[pad][id] == PAD_ON)
			{
				State = PAD_RELEASE;
			}
			else
			{
				State = PAD_OFF;
			}
			m_PadOldState[pad][id] = PAD_OFF;
		}
		break;
	}

	return State;
}


/**
 * �X�e�B�b�N�̏�Ԃ��擾����֐�
 * @param[in] id �`�F�b�N����X�e�B�b�N
 * @param[in] pad �`�F�b�N����GamePad
 * @return �X�e�B�b�N�̏��
 */
bool XInput::GetAnalogState(ANALOGPAD id, XINPUTPAD pad)
{
	switch (id)
	{
	case ANALOG_LEFT:
		if (m_PadControlState[pad].State.Gamepad.sThumbLX < -CONDEADZONE)
		{
			return true;
		}
		break;
	case ANALOG_RIGHT:
		if (m_PadControlState[pad].State.Gamepad.sThumbLX > CONDEADZONE)
		{
			return true;
		}

		break;
	case ANALOG_UP:
		if (m_PadControlState[pad].State.Gamepad.sThumbLY > CONDEADZONE)
		{
			return true;
		}

		break;
	case ANALOG_DOWN:
		if (m_PadControlState[pad].State.Gamepad.sThumbLY < -CONDEADZONE)
		{
			return true;
		}
		break;
	}

	return false;
}
