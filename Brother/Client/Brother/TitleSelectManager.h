#ifndef TITLESELECTMANAGER_H
#define TITLESELECTMANAGER_H

#define STARTPOS_X 1100
#define STARTPOS_Y 500
#define STAFFPOS_X 1100
#define STAFFPOS_Y 650
#define ENDPOS_X 190
#define ENDPOS_Y 600
#include "Library.h"

enum TITLEANIMA_ID;

//アナログパッドの入力でStartを指すか　Endを指すかが変化して、Aボタンを押したらTitleSceneに現在選択されてるものが何かを伝える
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
	int					m_alpha = 255;
	bool				m_isSelectFadeout = true;

public:
	TitleSelectManager(Library* pLibrary, bool* pPadState, bool* pPadOldState,PADSTATE* pButtonState);
	~TitleSelectManager();
	TITLESELECT_ID Control();
	void Draw();

};


#endif