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
	for (int count = 0; count < GAMEPAD_MAX; count++)
	{
		m_game_pad_state[count] = PAD_OFF;
	}
}

void XInput::Check(WORD button, int	pad)
{
	WORD ButtonState[GAMEPAD_MAX];
	static WORD OldButtons[GAMEPAD_MAX] = { PAD_OFF };
	XInputGetState(0, &m_game_pad.State);
	ButtonState[pad] = m_game_pad.State.Gamepad.wButtons;


	if (ButtonState[pad] != OldButtons[pad] && ButtonState[pad] != NO_SIGNAL
		&& OldButtons[pad] == NO_SIGNAL)
	{
		if (ButtonState[pad] & button)
		{
			m_game_pad_state[pad] = PAD_PUSH;
		}
	}

	if (ButtonState[pad] != OldButtons[pad] && OldButtons[pad] != NO_SIGNAL
		&& ButtonState[pad] == NO_SIGNAL)
	{
		m_game_pad_state[pad] = PAD_RELEASE;
	}

	if (ButtonState[pad] == OldButtons[pad] && ButtonState[pad] == button
		&& OldButtons[pad] == button)
	{
		if (ButtonState[pad] & button)
		{
			m_game_pad_state[pad] = PAD_ON;
		}
	}

	if (ButtonState[pad] == NO_SIGNAL && OldButtons[pad] == NO_SIGNAL)
	{
		m_game_pad_state[pad] = PAD_OFF;
	}

	OldButtons[pad] = ButtonState[pad];

}

bool XInput::L_Analog_Right()
{
	XInputGetState(0, &m_game_pad.State);
	if (m_game_pad.State.Gamepad.sThumbLX > CONDEADZONE)
	{
		return true;
	}
	return false;
}
bool XInput::L_Analog_Left()
{
	XInputGetState(0, &m_game_pad.State);
	if (m_game_pad.State.Gamepad.sThumbLX < -CONDEADZONE)
	{
		return true;
	}
	return false;
}
bool XInput::L_Analog_Up()
{
	XInputGetState(0, &m_game_pad.State);
	if (m_game_pad.State.Gamepad.sThumbLY > CONDEADZONE)
	{
		return true;
	}
	return false;
}
bool XInput::L_Analog_Down()
{
	XInputGetState(0, &m_game_pad.State);
	if (m_game_pad.State.Gamepad.sThumbLY < -CONDEADZONE)
	{
		return true;
	}
	return false;
}