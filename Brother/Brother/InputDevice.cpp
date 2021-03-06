/**
 * @file InputDevice.cpp
 * @brief InputDeviceクラス
 * @author 森本
 * @date 11月9日
 */

#include "InputDevice.h"



/**
 * InputDeviceクラスのコンストラクタ
 * @param[in] hWnd ウィンドウハンドル
 */
InputDevice::InputDevice(HWND hwnd) :
m_pDinput(NULL), 
m_pKeyDevice(NULL), 
m_pMouseDevice(NULL)
{
	m_hWnd = hwnd;
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDinput, NULL)))
	{
		MessageBox(0,"Directinputオブジェクト生成に失敗しました","InputDevice.cpp",MB_OK);
	}
}

/**
 * InputDeviceクラスのデストラクタ
 */
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
 * DirectInputのキーの初期化
 * @return 成功したかしてないか(成功したらS_OK)
 */
HRESULT InputDevice::InitDinputKey()
{
	HRESULT hr;

	//キーボードの初期化
	if (FAILED(hr = m_pDinput->CreateDevice(GUID_SysKeyboard,
		&m_pKeyDevice, NULL)))
	{
		return hr;
	}

	//データフォーマット
	if (FAILED(hr = m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}

	//協調レベル
	if (FAILED(hr = m_pKeyDevice->SetCooperativeLevel(
		m_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}

	m_pKeyDevice->Acquire();
	return S_OK;
}


/**
 * DirectInputのマウスの初期化
 * @return 成功したかしてないか(成功したらS_OK)
 */
HRESULT InputDevice::InitDinputMouse()
{
	HRESULT hr;


	//マウスの初期化
	if (FAILED(hr = m_pDinput->CreateDevice(GUID_SysMouse,
		&m_pMouseDevice, NULL)))
	{
		return hr;
	}

	//データフォーマット
	if (FAILED(hr = m_pMouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return hr;
	}

	//協調レベル
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


	// バッファ
	dipdw.dwData = BUFFER_SIZE;

	if (FAILED(hr = m_pMouseDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)))
	{
		return hr;
	}

	m_pMouseDevice->Acquire();
	return S_OK;
}

/**
 * キーの状態チェック関数
 * @param[out] Key キーの状態を格納する配列
 * @param[in] DIK チェックするキー
 */
void InputDevice::KeyCheck(KEYSTATE* Key, int DIK)
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
 * マウスの状態チェック関数
 * @param[out] Mouse マウスの状態を出力するMOUSEKIND構造体
 */
void InputDevice::MouseCheck(MOUSEKIND* Mouse)
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

