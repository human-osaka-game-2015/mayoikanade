#ifndef _INPUTDEVICE_H_
#define _INPUTDEVICE_H_


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
	KEYKIND_MAX
};


/**
 * マウスの状態の構造体
 */
typedef struct
{
	bool LEFT, RIGHT;
	int lx, ly, lz;

} MOUSEKIND;


class InputDevice
{
private:
	LPDIRECTINPUT8			m_pDinput;
	LPDIRECTINPUTDEVICE8	m_pKeyDevice;
	LPDIRECTINPUTDEVICE8	m_pMouseDevice;
	HWND					m_hWnd;			//

public:
	InputDevice(HWND hwnd);
	~InputDevice();
	HRESULT Init_Dinput_Key();
	HRESULT Init_Dinput_Mouse();
	void Key_Check(KEYSTATE* Key, int DIK);
	void Mouse_Check(MOUSEKIND* Mouse);

};

#endif