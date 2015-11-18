#include <windows.h>
#include <mmsystem.h>
#include <XInput.h>



#ifndef _XINPUT
#define _XINPUT
typedef struct
{
	XINPUT_STATE State;
	XINPUT_VIBRATION Vib_State;
}CONTROLER_STATE;



enum XINPUTPAD
{
	GAMEPAD_DPAD_UP,
	GAMEPAD_DPAD_DOWN,
	GAMEPAD_DPAD_LEFT,
	GAMEPAD_DPAD_RIGHT,
	GAMEPAD_START,
	GAMEPAD_BACK,
	GAMEPAD_LEFT_THUMB,
	GAMEPAD_RIGHT_THUMB,
	GAMEPAD_LEFT_SHOULDER,
	GAMEPAD_RIGHT_SHOULDER,
	GAMEPAD_A,
	GAMEPAD_B,
	GAMEPAD_X,
	GAMEPAD_Y,
	GAMEPAD_MAX
};


enum PADSTATE 
{
	PAD_PUSH,
	PAD_RELEASE,
	PAD_ON,
	PAD_OFF
};


/**
 * @brief 今回は解放をしないのでデストラクタは使わない
 */
class XInput
{
private:
	CONTROLER_STATE m_game_pad;
public:
	/**
	 * @brief キー状態全てにOFFを入れる
	 */
	XInput();
	~XInput(){};

	/**
	* @brief Xboxコントローラーの入力状態を格納している
	*/
	int m_game_pad_state[GAMEPAD_MAX];

	/**
	 * @brief Xboxコントローラーのボタンを取る
	 * @param Button 取りたいボタンの値を渡す。中身はXInput.hにdefineされている。
	 * GAMEPAD_DPAD_DOWNなど
	 * @param Pad　入力状態を入れるため、格納したい配列の要素数を渡す。変数はクラス内にある
	 * @return なし
	 */
	void Check(WORD button, int Pad);
	
	/**
	* @brief 左のアナログパッドの右が倒れたとき
	* @return 処理結果(入力されたときtrueされてないときfalseが返る)
	*/
	bool L_Analog_Right();
	
	/**
	* @brief　左のアナログパッドの左が倒れたとき
	* @return 処理結果(入力されたときtrueされてないときfalseが返る)
	*/
	bool L_Analog_Left();
	
	/**
	* @brief 左のアナログパッドの上が倒れたとき
	* @return 処理結果(入力されたときtrueされてないときfalseが返る)
	*/
	bool L_Analog_Up();

	/**
	* @brief 左のアナログパッドの下が倒れたとき
	* @return 処理結果(入力されたときtrueされてないときfalseが返る)
	*/
	bool L_Analog_Down();

};

#endif
