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
 * @brief ����͉�������Ȃ��̂Ńf�X�g���N�^�͎g��Ȃ�
 */
class XInput
{
private:
	CONTROLER_STATE m_game_pad;
public:
	/**
	 * @brief �L�[��ԑS�Ă�OFF������
	 */
	XInput();
	~XInput(){};

	/**
	* @brief Xbox�R���g���[���[�̓��͏�Ԃ��i�[���Ă���
	*/
	int m_game_pad_state[GAMEPAD_MAX];

	/**
	 * @brief Xbox�R���g���[���[�̃{�^�������
	 * @param Button ��肽���{�^���̒l��n���B���g��XInput.h��define����Ă���B
	 * GAMEPAD_DPAD_DOWN�Ȃ�
	 * @param Pad�@���͏�Ԃ����邽�߁A�i�[�������z��̗v�f����n���B�ϐ��̓N���X���ɂ���
	 * @return �Ȃ�
	 */
	void Check(WORD button, int Pad);
	
	/**
	* @brief ���̃A�i���O�p�b�h�̉E���|�ꂽ�Ƃ�
	* @return ��������(���͂��ꂽ�Ƃ�true����ĂȂ��Ƃ�false���Ԃ�)
	*/
	bool L_Analog_Right();
	
	/**
	* @brief�@���̃A�i���O�p�b�h�̍����|�ꂽ�Ƃ�
	* @return ��������(���͂��ꂽ�Ƃ�true����ĂȂ��Ƃ�false���Ԃ�)
	*/
	bool L_Analog_Left();
	
	/**
	* @brief ���̃A�i���O�p�b�h�̏オ�|�ꂽ�Ƃ�
	* @return ��������(���͂��ꂽ�Ƃ�true����ĂȂ��Ƃ�false���Ԃ�)
	*/
	bool L_Analog_Up();

	/**
	* @brief ���̃A�i���O�p�b�h�̉����|�ꂽ�Ƃ�
	* @return ��������(���͂��ꂽ�Ƃ�true����ĂȂ��Ƃ�false���Ԃ�)
	*/
	bool L_Analog_Down();

};

#endif
