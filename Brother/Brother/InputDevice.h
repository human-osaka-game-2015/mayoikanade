#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H


#define BUFFER_SIZE  64
#define DIRECTINPUT_VERSION 0x0800

#include <windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <dinput.h>



/**
 * KEY状態の列挙
 */
enum KEYSTATE
{
	PUSH,
	RELEASE,
	ON,
	OFF,
	KEYSTATE_MAX
};


/**
 * KEY種類の列挙
 */
enum KEYKIND
{
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_FIRE,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_SPACE,
	KEY_ESC,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_BACKSPACE,
	KEY_COMMA,
	KEYKIND_MAX
};


/**
 * マウスの状態の構造体
 */
struct MOUSEKIND
{
	bool LEFT, RIGHT;
	int lx, ly, lz;

};


class InputDevice
{
private:
	LPDIRECTINPUT8			m_pDinput;
	LPDIRECTINPUTDEVICE8	m_pKeyDevice;
	LPDIRECTINPUTDEVICE8	m_pMouseDevice;
	HWND					m_hWnd;

public:
	InputDevice(HWND hwnd);
	~InputDevice();
	HRESULT InitDinputKey();
	HRESULT InitDinputMouse();
	void KeyCheck(KEYSTATE* Key, int DIK);
	void MouseCheck(MOUSEKIND* Mouse);

};

#endif