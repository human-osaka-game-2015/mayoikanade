#include "XInput_lib.h"
#define CONDEADZONE   65535/4 //コントローラーのデッドゾーン
#define NO_SIGNAL 0x0000

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"xinput.lib ")


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


void XInput::Check(XINPUTPAD pad)
{
	XInputGetState(pad, &m_PadControlState[pad].State);
}


PADSTATE XInput::GetButtonState(XINPUT_ID id, XINPUTPAD pad)
{
	PADSTATE State;

	switch (id)
	{
	case GAMEPAD_A:
		//入力されていて
		if (m_PadControlState[pad].State.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			//前も入力されてたら
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
			//前も入力されてたら
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
		//入力されていて
		if (m_PadControlState[pad].State.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			//前も入力されてたら
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
			//前も入力されてたら
			if (m_PadOldState[pad][id] == PAD_ON)
			{
				State = PAD_RELEASE;
			}
			else
			{
				State = PAD_OFF;
			}
			break;
		}
	}

	return State;
}


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
