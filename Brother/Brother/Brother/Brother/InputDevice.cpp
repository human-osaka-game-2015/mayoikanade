/**
 * @file InputDevice.cpp
 * @brief InputDevice�N���X
 * @author �X�{
 * @date 11��9��
 */

#include "InputDevice.h"




InputDevice::InputDevice(HWND hwnd) :m_pDinput(NULL), m_pKeyDevice(NULL), m_pMouseDevice(NULL)
{
	m_hWnd = hwnd;
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDinput, NULL)))
	{
		MessageBox(0,"Directinput�I�u�W�F�N�g�����Ɏ��s���܂���","",MB_OK);
	}
}

InputDevice::~InputDevice()
{
	
	if (m_pKeyDevice != NULL)
	{
		m_pKeyDevice->Release();
	}

	if (m_pMouseDevice != NULL)
	{
		m_pMouseDevice->Release();
	}

	m_pDinput->Release();
}


/**
* �_�C���N�g�C���v�b�g�̃L�[�{�[�h������
*/
HRESULT InputDevice::Init_Dinput_Key()
{
	HRESULT hr;

	//�L�[�{�[�h�̏�����
	if (FAILED(hr = m_pDinput->CreateDevice(GUID_SysKeyboard,
		&m_pKeyDevice, NULL)))
	{
		return hr;
	}

	//�f�[�^�t�H�[�}�b�g
	if (FAILED(hr = m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}

	//�������x��
	if (FAILED(hr = m_pKeyDevice->SetCooperativeLevel(
		m_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}

	m_pKeyDevice->Acquire();
	return S_OK;
}


/**
* �_�C���N�g�C���v�b�g�̃}�E�X������
*/
HRESULT InputDevice::Init_Dinput_Mouse()
{
	HRESULT hr;


	//�}�E�X�̏�����
	if (FAILED(hr = m_pDinput->CreateDevice(GUID_SysMouse,
		&m_pMouseDevice, NULL)))
	{
		return hr;
	}

	//�f�[�^�t�H�[�}�b�g
	if (FAILED(hr = m_pMouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return hr;
	}

	//�������x��
	if (FAILED(hr = m_pMouseDevice->SetCooperativeLevel(m_hWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}

	DIPROPDWORD dipdw;
	// the header
	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;


	if (FAILED(hr = m_pMouseDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph)))
	{
		return hr;
	}


	// �o�b�t�@
	dipdw.dwData = BUFFER_SIZE;

	if (FAILED(hr = m_pMouseDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)))
	{
		return hr;
	}

	m_pMouseDevice->Acquire();
	return S_OK;
}






/**
* KEYSTATE* Key�̓L�[�̏�Ԃ�ۑ�����ꏊ(KEYSTATE�^��test_lib.h�Ő錾���Ă���)
* int DIK��Directinput�̕������ʃR�[�h�A��Ԃ��`�F�b�N�������L�[�̏�Ԃ�ۑ�����
* LPDIRECTINPUTDEVICE8�@�̓f�o�C�X�̃I�u�W�F�N�g
*/
void InputDevice::Key_Check(KEYSTATE* Key, int DIK)
{
	BYTE diks[256];
	static int old_diks[256] = { OFF };

	HRESULT hr = m_pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		m_pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		if (diks[DIK] & 0x80)
		{
			if (old_diks[DIK] == OFF)
			{
				*Key = PUSH;
			}
			else
			{
				*Key = ON;
			}
			old_diks[DIK] = ON;
		}
		else
		{
			if (old_diks[DIK] == ON)
			{
				*Key = RELEASE;
			}
			else
			{
				*Key = OFF;
			}
			old_diks[DIK] = OFF;
		}
	}
}



/**
*�}�E�X�̏�Ԃ��`�F�b�N����֐�
*MOUSEKIND�̓}�E�X�̏�Ԃ��i�[����\����
*��x�ĂԂ����ł��ׂĂ̏�Ԃ��Ƃ��Ă����B
*/
void InputDevice::Mouse_Check(MOUSEKIND* Mouse)
{
	DIMOUSESTATE dims;
	HRESULT hr;

	
	m_pMouseDevice->Acquire();

	hr = m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &dims);
	if (SUCCEEDED(hr))
	{
		if (dims.rgbButtons[0])
		{
			Mouse->LEFT = true;
		}
		else
		{
			Mouse->LEFT = false;
		}

		if (dims.rgbButtons[1])
		{
			Mouse->RIGHT = true;
		}
		else
		{
			Mouse->RIGHT = false;
		}

		if (dims.lX)
		{
			Mouse->lx = dims.lX;
		}

		if (dims.lY)
		{
			Mouse->ly = dims.lY;
		}

		if (dims.lZ)
		{
			Mouse->lz = dims.lZ;
		}
	}
}
