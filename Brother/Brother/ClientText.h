#ifndef CLIENTTEXT_H
#define CLIENTTEXT_H
#include "Vertex.h"
#include "ServerText.h"

class Library;
class ClientModeManager;
enum GAMEMODE_NUM;
enum PADSTATE;


class ClientText
{
private:
	Library*			m_pLibrary;
	ClientModeManager*	m_pModeManager;
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

	bool*				m_pPadState;			//���݂̃L�[���
	bool*				m_pPadOldState;			//�ЂƂO�̃L�[���
	PADSTATE*			m_pButtonState;			//���݂̃{�^�����

public:
	ClientText(Library* pLibrary, bool* pPadState, bool* pPadOldState, PADSTATE* pButtonState);
	~ClientText();
	void Control();
	void Draw();
	void ModeManagerSet(ClientModeManager* pModeManager);
	void TextControl();
	void TextDraw();
	bool GetMessageEnd();

};
#endif
