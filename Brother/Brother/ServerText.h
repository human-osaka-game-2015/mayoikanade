#ifndef ServerTEXT_H
#define ServerTEXT_H
#include "Vertex.h"

#define LIGHT_INTENSITY 100 //どのぐらいの明るさで、メインのマップを残すかです。
#define LAST_LIGHT 1100 //メッセージの幅と同じにします。

#define TEXT_SPEED 5 //会話のテキストを表示するのにかかる時間
#define TEXT_SEND  LAST_LIGHT/60/TEXT_SPEED //１フレームあたり、右の辺がどの程度動くか。

class Library;
class ServerModeManager;
enum GAMEMODE_NUM;

enum PADSTATE;

enum TEXT_NUM
{
	DARKNESS,
	BROTHER_A,
	BROTHER_O,
	NAMEBOX_A,
	NAMEBOX_O,
	TEXTBOX,
	MESSAGE_A,
	MESSAGE_O,
	TEXTMAX
};

class ServerText
{
private:
	Library*			m_pLibrary;
	ServerModeManager*	m_pModeManager;
	GAMEMODE_NUM		m_CurrentMode;
	Position m_Pos[TEXTMAX];
	
	int m_darkness_alpha;
	int m_brother_alpha;
	int m_textbox_alpha;
	int m_message_count;
	int m_message_old;
	int m_send_count;

	double m_message_UV;

	float m_message_right;

	bool m_text_is_unsolved;
	bool m_all_alpha_is_max;
	bool m_text_is_end;
	bool m_message_wait;

	bool*				m_pPadState;			//現在のキー状態
	bool*				m_pPadOldState;			//ひとつ前のキー状態
	PADSTATE*			m_pButtonState;			//現在のボタン状態
public:
	ServerText(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState);
	~ServerText();
	void Control();
	void Draw();
	void ModeManagerSet(ServerModeManager* pModeManager);
	void TextControl();
	void TextDraw();
	bool GetMessageEnd();
};

#endif