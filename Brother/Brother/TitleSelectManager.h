#ifndef TITLESELECTMANAGER_H
#define TITLESELECTMANAGER_H

#define STARTPOS_X 1100
#define STARTPOS_Y 500
#define STAFFPOS_X 1100
#define STAFFPOS_Y 650
#define ENDPOS_X 190
#define ENDPOS_Y 600
#define CURSOL_WIDTH 100
#define CURSOL_HEIGHT 130
#define SELECT_ALPHA_MIN 200		//�I�����ڂ̍ŏ�alpha�l	
#define SELECT_ALPHA_MAX 255		//�I�����ڂ̍ő�alpha�l
#define START_CURSOL_POSX 900		//START��I�����Ă���Ƃ��̃J�[�\���̈ʒu
#define START_CURSOL_POSY 490		//START��I�����Ă���Ƃ��̃J�[�\���̈ʒu
#define STAFF_CURSOL_POSX 900		//STAFF��I�����Ă���Ƃ��̃J�[�\���̈ʒu
#define STAFF_CURSOL_POSY 640		//STAFF��I�����Ă���Ƃ��̃J�[�\���̈ʒu
#define END_CURSOL_POSX 190			//END��I�����Ă���Ƃ��̃J�[�\���̈ʒu
#define END_CURSOL_POSY 500			//END��I�����Ă���Ƃ��̃J�[�\���̈ʒu


#include "Library.h"

enum TITLEANIMA_ID;


enum TITLESELECT_ID
{
	GAME_START,
	GAME_STAFF,
	GAME_END,
	TITLESELECT_NONE,
};


class TitleSelectManager
{
private:
	Library*			m_pLibrary;
	Position			m_StartPos;
	Position			m_StaffPos;
	Position			m_EndPos;
	Position			m_CursolPos;
	TITLESELECT_ID		m_CurrentSelect;
	TITLEANIMA_ID		m_CursolCurrentAnima;
	PADSTATE*			m_pButtonState;

	bool*				m_PadState;
	bool*				m_PadOldState;
	int					m_alpha;
	bool				m_isSelectFadeout = true;

public:
	TitleSelectManager(Library* pLibrary, bool* pPadState, bool* pPadOldState,PADSTATE* pButtonState);
	~TitleSelectManager();
	TITLESELECT_ID Control();
	void Draw();

};


#endif